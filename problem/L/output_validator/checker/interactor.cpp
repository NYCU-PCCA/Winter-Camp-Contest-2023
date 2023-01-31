#include "BigInt.hpp"
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> struct P {
  T x, y;
  P(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(const P &p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(const P &p) const { return tie(x, y) == tie(p.x, p.y); }
  bool operator!=(const P &p) const { return tie(x, y) != tie(p.x, p.y); }
  P operator-() const { return {-x, -y}; }
  P operator+(P p) const { return {x + p.x, y + p.y}; }
  P operator-(P p) const { return {x - p.x, y - p.y}; }
  P operator*(T d) const { return {x * d, y * d}; }
  P operator/(T d) const { return {x / d, y / d}; }
  T dist2() const { return x * x + y * y; }
  double len() const { return sqrt(dist2()); }
  P unit() const { return *this / len(); }
  friend T dot(P a, P b) { return a.x * b.x + a.y * b.y; }
  friend T cross(P a, P b) { return a.x * b.y - a.y * b.x; }
  friend T cross(P a, P b, P o) { return cross(a - o, b - o); }
};
using pt = P<ll>;

constexpr ll INF = 1'000'000'000'000'000'000;

bool readAns(InStream &stream, vector<pt> &points) {
  vector<BigInt> pa(2), qa(2), pb(2), qb(2), pc(2), qc(2);
  for (int i = 0; i < 2; i++) {
    pa[i] = stream.readLong(-INF, INF, "pa_" + to_string(i));
    qa[i] = stream.readLong(-INF, INF, "qa_" + to_string(i));
    pb[i] = stream.readLong(-INF, INF, "pb_" + to_string(i));
    qb[i] = stream.readLong(-INF, INF, "qb_" + to_string(i));
    pc[i] = stream.readLong(-INF, INF, "pc_" + to_string(i));
    qc[i] = stream.readLong(-INF, INF, "qc_" + to_string(i));
    if (pa[i] == 0 || pb[i] == 0 || pc[i] == 0) {
      stream.quitf(_wa, "denominator = 0");
    }
    if (pa[i] < 0) {
      pa[i] = -pa[i];
      qa[i] = -qa[i];
    }
    if (pb[i] < 0) {
      pb[i] = -pb[i];
      qb[i] = -qb[i];
    }
    if (pc[i] < 0) {
      pc[i] = -pc[i];
      qc[i] = -qc[i];
    }
  }
  int n = points.size();
  vector<int> type(n);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) {
      auto x = points[j].x, y = points[j].y;
      auto l = pc[i] * (qa[i] * pb[i] * x + pa[i] * qb[i] * y);
      auto r = pa[i] * pb[i] * qc[i];
      if (l == r) {
        stream.quitf(_wa, "point %d is on line %d", j + 1, i + 1);
      } else if (l > r) {
        type[j] |= (1 << i);
      }
    }
  }
  vector<int> cnt(4);
  for (int j = 0; j < n; j++) {
    cnt[type[j]]++;
  }
  for (int i = 0; i < 4; i++) {
    if (cnt[i] != n / 4) {
      stream.quitf(_wa,
                   "one of the regions does not contain exactly n/4 points");
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);
  int n = inf.readInt();
  vector<pt> points(n);
  for (int i = 0; i < n; i++) {
    points[i].x = inf.readInt();
    points[i].y = inf.readInt();
  }

  bool jans = readAns(ans, points);
  bool pans = readAns(ouf, points);

  if (!jans) {
    quitf(_fail, "jury's answer is incorrect");
  } else if (!pans) {
    quitf(_wa, "participant's answer is incorrect");
  } else {
    quitf(_ok, "both got correct solutions");
  }
}
