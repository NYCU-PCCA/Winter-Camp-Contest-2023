ARG DOM_VERSION=8.1.3
FROM domjudge/judgehost:${DOM_VERSION}

ARG KOTLIN_VERSION=1.8.0

RUN : \
    && apt-get update \
    && apt-get install --no-install-recommends --no-install-suggests -y \
        unzip curl \
    && curl -L -o /tmp/kotlin-compiler.zip https://github.com/JetBrains/kotlin/releases/download/v${KOTLIN_VERSION}/kotlin-compiler-${KOTLIN_VERSION}.zip \
    && unzip /tmp/kotlin-compiler.zip -d /chroot/domjudge/usr/local \
    && ln -s /usr/local/kotlinc/bin/kotlin /chroot/domjudge/usr/bin \
    && ln -s /usr/local/kotlinc/bin/kotlinc /chroot/domjudge/usr/bin \
    && rm /tmp/kotlin-compiler.zip \
    && rm -rf /var/lib/apt/lists/* \
    && :
