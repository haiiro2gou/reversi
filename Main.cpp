#include <climits>
#include <iostream>
#include <vector>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define rrep(i,a,b) for(int i=a;i>=b;i--)
#define fore(i,a) for(auto &i:a)
#define all(x) x.begin(),x.end()
using namespace std; void _main(); int main() { cin.tie(nullptr); ios::sync_with_stdio(false); _main(); }
typedef long long ll; const int inf = INT_MAX / 2; const ll infl = 1LL << 60;
template<class T> bool chmax(T &a, const T &b) { if (a<b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T &a, const T &b) { if (b<a) { a = b; return 1; } return 0; }

int N = 26, T = 0, cnt_b, cnt_w;
vector<vector<int>> board(N+2, vector<int>(N+2));
int player = -1;

void make_board() {
  rep(i, 0, N+2) {
    board[0][i] = 2; board[N+1][i] = 2;
    board[i][0] = 2; board[i][N+1] = 2;
  }
  board[N/2][N/2] = 1; board[N/2+1][N/2+1] = 1;
  board[N/2][N/2+1] = -1; board[N/2+1][N/2] = -1;
}

void show_board() {
  rep(h, 0, N+1) {
    rep(w, 0, N+1) {
      switch (board[h][w]) {
        case -1:
          cout << "●";
          break;
        case 1:
          cout << "○";
          break;
        case 0:
          cout << "-";
          break;
        case 2:
          if (h == 0 && w != 0) cout << (char)('a' + w - 1);
          else if (h != 0 && w == 0) cout << (char)('0' + h);
          else cout << " ";
          break;
        default:
          break;
      }
    }
    cout << endl;
  }
}

void show_player() {
  switch (player) {
    case -1:
      cout << "先手の手番です" << endl;
      break;
    case 1:
      cout << "後手の手番です" << endl;
      break;
    default:
      break;
  }
}

int check_dir(int h, int w, int dir_h, int dir_w) {
  int cnt = 1;
  while (board[h+dir_h*cnt][w+dir_w*cnt] == player*-1) cnt++;
  if (board[h+dir_h*cnt][w+dir_w*cnt] == player) return cnt-1;
  return 0;
}

bool check_place(int h, int w) {
  if (board[h][w] == 0) {
    rep(dir_h, -1, 2) rep(dir_w, -1, 2) {
      if (check_dir(h, w, dir_h, dir_w)) return true;
    }
  }
  return false;
}

bool is_finished() {
  rep(h, 1, N+1) rep(w, 1, N+1) if (check_place(h, w)) return false;
  player *= -1;
  rep(h, 1, N+1) rep(w, 1, N+1) if (check_place(h, w)) {
    cout << "置くことが可能なマスが存在しません" << endl;
    cout << "手番を変更しました" << endl;
    return false;
  }
  return true;
}

void place_stone(int h, int w) {
  rep(dir_h, -1, 2) rep(dir_w, -1, 2) {
    int diff = check_dir(h, w, dir_h, dir_w);
    rep(i, 1, diff+1) board[h+dir_h*i][w+dir_w*i] = player;
  }
  board[h][w] = player;
}

void count_stone() {
  cnt_b = 0; cnt_w = 0;
  rep(h, 1, N+1) rep(w, 1, N+1) {
    if (board[h][w] == -1) cnt_b++;
    if (board[h][w] == 1) cnt_w++;
  }
  printf("%d手目 ●:%d ○:%d\n", T, cnt_b, cnt_w); fflush(stdout);
}

void judge_winner() {
  if (cnt_w < cnt_b) cout << "先手の勝利" << endl;
  else if (cnt_b < cnt_w) cout << "後手の勝利" << endl;
  else cout << "引き分け" << endl;
}

void _main() {
  printf("盤のサイズを入力してください(4 ~ 26)\n> "); fflush(stdout);
  string s; cin >> s;
  int ss = stoi(s);
  if (4 <= ss && ss <= 26 && ss % 2 == 0) N = ss;
  else {
    printf("エラーが発生しました\n盤のサイズを8に設定します\n"); fflush(stdout);
    N = 8;
  }
  make_board();
  while (!is_finished()) {
    show_board();
    count_stone();
    show_player();
    int h, w;
    string pos;
    do {
      printf("駒の位置を入力してください(例:a1)\n> "); fflush(stdout);
      cin >> pos;
      if (pos.length() == 2 && pos[0] - 'a' < N && pos[1] - '0' <= N) {
        w = tolower(pos[0]) - 'a' + 1;
        h = pos[1] - '0';
      } else {
        h = N / 2; w = N / 2;
      }
    } while (!check_place(h, w));
    place_stone(h, w);
    player *= -1;
    T++;
  }
  show_board();
  count_stone();
  judge_winner();
}
