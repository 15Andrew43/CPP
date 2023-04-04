#include <iostream>
#include <vector>
#include <algorithm>

struct Team {
    int team_number_;
    int score_;
    int time_;
};

bool comp(Team a, Team b) {
    if (a.score_ > b.score_) {
        return true;
    } else if (a.score_ < b.score_) {
        return false;
    }
    if (a.time_ < b.time_) {
        return true;
    } else if (a.time_ > b.time_) {
        return false;
    }
    return a.team_number_ < b.team_number_;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Team> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
        int s, t;
        std::cin >> s >> t;
        v.push_back({i, s, t});
    }
    sort(v.begin(), v.end(), comp);

    for (Team x : v) {
        std::cout << x.team_number_ + 1 << '\n';
    }
    return 0;
}