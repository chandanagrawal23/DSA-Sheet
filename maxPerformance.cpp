//https://leetcode.com/problems/maximum-performance-of-a-team/
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
    vector<pair<int, int>> eff_sp;
    priority_queue <int, vector<int>, greater<int> > pq_speeds;
    long sum = 0, res = 0;
    for (auto i = 0; i < n; ++i)
        eff_sp.push_back({efficiency[i], speed[i]});
    sort(begin(eff_sp), end(eff_sp));
    for (auto i = n - 1; i >= 0; --i) {
        sum += eff_sp[i].second;
        pq_speeds.push(eff_sp[i].second);
        if (pq_speeds.size() > k) {
            sum -= pq_speeds.top();
            pq_speeds.pop();
        }
        res = max(res, sum * eff_sp[i].first);
    }
    return res % 1000000007;
}
};
