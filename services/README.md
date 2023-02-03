## Bugs

- 要先在 domjudge finalize 才有 first solve
- award.sh medal 設 0 傳不上去
- live 的 Statistics 解題數量寬度錯誤 (finalize 前？

## Network

- DOMserver: 10.254.10.254 + public ip
- judgehost: 10.254.10.1 ~ 

## DOMJudge

### Setup ENV

```sh
echo 'LANG=en_US.UTF-8' | tee /etc/default/locale
DEBIAN_FRONTEND=noninteractive dpkg-reconfigure locales
timedatectl set-timezone Asia/Taipei

apt install -y tmux vim curl git zsh htop mtr net-tools nload qemu-guest-agent
systemctl start qemu-guest-agent

apt install -y vim curl htop mtr net-tools nload

curl -sL git.io/nella17-setup.sh | bash -x
vim +PlugUpdate +qall
zsh ~/.zim/zimfw.zsh install
sudo chsh -s `which zsh` $USER
```

### Setup Router

```sh
ssh-keygen -t ed25519
cat ~/.ssh/id_ed25519.pub

echo 'net.ipv4.conf.default.rp_filter=1
net.ipv4.conf.all.rp_filter=1
net.ipv4.ip_forward=1' | tee /etc/sysctl.d/1-forward.conf
sysctl -p --system

iptables -t nat -A POSTROUTING -s 10.254.10.0/24 -o eth0 -j MASQUERADE
iptables -A FORWARD -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
iptables -A FORWARD -i eth1 -j ACCEPT
```

### Sync Time & Setup Docker & Disable timer

```sh
apt install -y ntp
ntpq -p

curl -sL get.docker.io | bash

systemctl disable apt-daily-upgrade.timer
systemctl stop apt-daily-upgrade.timer
systemctl disable apt-daily.timer
systemctl stop apt-daily.timer
```

### Setup Domjudge

```sh
docker compose up -d
docker compose exec -it domjudge cat /opt/domjudge/domserver/etc/initial_admin_password.secret | less
docker compose exec -it domjudge cat /opt/domjudge/domserver/etc/restapi.secret | less
```

## Judgehost

### Setup ENV

```sh
sed -i '/^#.* en_US.UTF-8* /s/^# //' /etc/locale.gen
DEBIAN_FRONTEND=noninteractive dpkg-reconfigure locales
timedatectl set-timezone Asia/Taipei
apt install -y vim htop mtr nload qemu-guest-agent
systemctl start qemu-guest-agent
```

### Build judgehost image support Kotlin

```sh
docker build \
    --build-arg DOM_VERSION=8.1.3 \
    --build-arg KOTLIN_VERSION=1.8.0 \
    judgehost -t nella17/judgehost:8.1.3
docker login
docker push nella17/judgehost:8.1.3
docker logout
```

### Setup judgehost

```sh
sed -i \
    -e 's:GRUB_CMDLINE_LINUX_DEFAULT=.*:GRUB_CMDLINE_LINUX_DEFAULT="cgroup_enable=memory swapaccount=1 isolcpus=2 systemd.unified_cgroup_hierarchy=0":' \
    /etc/default/grub
update-grub
echo kernel.randomize_va_space=0 | tee /etc/sysctl.d/2-no-aslr.conf
sysctl -p --system
reboot

echo 127.0.0.1 "${HOSTNAME#*-}" | tee -a /etc/hosts

rv () {
    echo -n "$1 : " >&2
    read x
    echo $x
}

docker run -d \
   --restart=on-failure \
   --network host \
   --privileged \
   -v "/sys/fs/cgroup:/sys/fs/cgroup" \
   --name judgehost \
   --hostname "${HOSTNAME#*-}" \
   -e "CONTAINER_TIMEZONE=Asia/Taipei" \
   -e "DOMSERVER_BASEURL=$(rv url)" \
   -e "JUDGEDAEMON_USERNAME=$(rv username)" \
   -e "JUDGEDAEMON_PASSWORD=$(rv password)" \
   nella17/judgehost:8.1.3
```

## Helper cmds

```sh
docker stop judgehost && docker rm judgehost
docker restart judgehost
docker logs -f judgehost
```

```sh
docker exec -it judgehost dj_run_chroot bash

apt install -y zip unzip curl
export SDKMAN_DIR="/usr/local/sdkman"
curl -s "https://get.sdkman.io" | bash
source "$SDKMAN_DIR/bin/sdkman-init.sh"
sdk version
sdk install kotlin
ln -s $SDKMAN_DIR/kotlin /usr/bin
ln -s $SDKMAN_DIR/kotlinc /usr/bin

KOTLIN_VERSION=1.8.0
apt install -y zip unzip curl
curl -L -o /tmp/kotlin-compiler.zip https://github.com/JetBrains/kotlin/releases/download/v${KOTLIN_VERSION}/kotlin-compiler-${KOTLIN_VERSION}.zip
unzip /tmp/kotlin-compiler.zip -d /usr/local
rm /tmp/kotlin-compiler.zip
ln -s /usr/local/kotlinc/bin/kotlin /usr/bin
ln -s /usr/local/kotlinc/bin/kotlinc /usr/bin
```

```sh
apt install -y openssh-server
vim /etc/network/interfaces
```

```sql
select s.submitid, s.langid, j.result, max(jr.runtime) from submission s join judging j on s.submitid = j.submitid join judging_run jr on j.judgingid = jr.judgingid where j.valid and s.probid = 4 group by s.submitid;
```
