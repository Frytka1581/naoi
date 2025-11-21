#include <bits/stdc++.h>
using namespace std;

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

vector<tuple<int, int, int>> reverse_moves(const vector<tuple<int, int, int>>& forward, const vector<pair<int, int>>& start_pos) {
  vector<pair<int, int>> pos = start_pos;
  vector<pair<int, int>> froms;
  for (auto &m : forward) {
    auto [c, i, j] = m;
    froms.push_back(pos[c]);
    pos[c] = {i, j};
  }
  vector<tuple<int, int, int>> rev;
  for (int l = forward.size() - 1; l >= 0; l--) {
    auto [c, i, j] = forward[l];
    auto fr = froms[l];
    rev.push_back(make_tuple(c, fr.first, fr.second));
  }
  return rev;
}

vector<tuple<int, int, int>> get_moves(const vector<pair<int, int>>& initial_pos, const vector<pair<int, int>>& Q, int n, int k, bool& possible) {
  vector<tuple<int, int, int>> moves;
  vector<pair<int, int>> current_pos = initial_pos;
  vector<bool> done(k + 1, false);
  int remaining = k;
  possible = true;
  while (remaining > 0) {
    bool moved = false;
    for (int id = 1; id <= k; id++) {
      if (done[id]) continue;
      int sx = current_pos[id].first, sy = current_pos[id].second;
      int tx = Q[id].first, ty = Q[id].second;
      if (sx == tx && sy == ty) {
        done[id] = true;
        remaining--;
        moved = true;
        continue;
      }
      vector<vector<bool>> forbidden(n + 1, vector<bool>(n + 1, false));
      for (int j = 1; j <= k; j++) {
        if (j != id) {
          int rx = current_pos[j].first, ry = current_pos[j].second;
          for (int d1 = -1; d1 <= 1; d1++) {
            for (int d2 = -1; d2 <= 1; d2++) {
              int nx = rx + d1, ny = ry + d2;
              if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) forbidden[nx][ny] = true;
            }
          }
        }
      }
      if (forbidden[tx][ty]) continue;
      vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false));
      vector<vector<pair<int, int>>> parent(n + 1, vector<pair<int, int>>(n + 1, {-1, -1}));
      queue<pair<int, int>> q;
      q.push({sx, sy});
      visited[sx][sy] = true;
      bool reached = false;
      while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == tx && y == ty) {
          reached = true;
          break;
        }
        for (int d = 0; d < 8; d++) {
          int nx = x + dx[d], ny = y + dy[d];
          if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !forbidden[nx][ny] && !visited[nx][ny]) {
            visited[nx][ny] = true;
            parent[nx][ny] = {x, y};
            q.push({nx, ny});
          }
        }
      }
      if (!reached) continue;
      vector<pair<int, int>> path;
      pair<int, int> cur = {tx, ty};
      while (cur.first != sx || cur.second != sy) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
      }
      path.push_back({sx, sy});
      reverse(path.begin(), path.end());
      for (size_t l = 1; l < path.size(); l++) {
        moves.push_back(make_tuple(id, path[l].first, path[l].second));
      }
      current_pos[id] = {tx, ty};
      done[id] = true;
      remaining--;
      moved = true;
    }
    if (!moved) {
      possible = false;
      return {};
    }
  }
  return moves;
}

int main() {
  int n, k;
  cin >> n >> k;
  vector<vector<int>> start_board(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> start_board[i][j];
  vector<vector<int>> final_board(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> final_board[i][j];
  vector<pair<int, int>> start_pos(k + 1, {0, 0});
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (start_board[i][j] > 0) start_pos[start_board[i][j]] = {i, j};
  vector<pair<int, int>> target_pos(k + 1, {0, 0});
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (final_board[i][j] > 0) target_pos[final_board[i][j]] = {i, j};
  int half = (n + 1) / 2;
  int max_k_ = half * half;
  if (k == max_k_) {
    if (start_board == final_board) {
      cout << "TAK" << endl;
      cout << 0 << endl;
    } else {
      cout << "NIE" << endl;
    }
    return 0;
  }
  vector<pair<int, int>> Q(k + 1);
  int idx = 1;
  for (int i = 0; i < half; i++) {
    for (int j = 0; j < half; j++) {
      if (idx > k) break;
      Q[idx] = {2 * i + 1, 2 * j + 1};
      idx++;
    }
    if (idx > k) break;
  }
  bool possible1, possible2;
  auto initial_moves = get_moves(start_pos, Q, n, k, possible1);
  if (!possible1) {
    cout << "NIE" << endl;
    return 0;
  }
  auto final_moves = get_moves(target_pos, Q, n, k, possible2);
  if (!possible2) {
    cout << "NIE" << endl;
    return 0;
  }
  auto canonical_to_final = reverse_moves(final_moves, target_pos);
  vector<tuple<int, int, int>> all_moves;
  for (auto &m : initial_moves) all_moves.push_back(m);
  for (auto &m : canonical_to_final) all_moves.push_back(m);
  cout << "TAK" << endl;
  cout << all_moves.size() << endl;
  for (auto &m : all_moves) {
    auto [c, i, j] = m;
    cout << c << " " << i << " " << j << endl;
  }
  return 0;
}