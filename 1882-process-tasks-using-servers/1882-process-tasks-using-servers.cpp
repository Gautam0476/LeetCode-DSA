
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        // Free servers: {weight, index}
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> freeServers;

        // Busy servers: {free time, index}
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> busyServers;

        for (int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        vector<int> ans;
        long long time = 0;

        for (int i = 0; i < m; i++) {
            time = max(time, (long long)i);

            // Release all servers that have completed their tasks
            while (!busyServers.empty() &&
                   busyServers.top().first <= time) {

                int idx = busyServers.top().second;
                busyServers.pop();

                freeServers.push({servers[idx], idx});
            }

            // If no server is free, wait for the earliest one
            if (freeServers.empty()) {
                time = busyServers.top().first;

                while (!busyServers.empty() &&
                       busyServers.top().first <= time) {

                    int idx = busyServers.top().second;
                    busyServers.pop();

                    freeServers.push({servers[idx], idx});
                }
            }

            // Select server with minimum weight, then minimum index
            auto [weight, idx] = freeServers.top();
            freeServers.pop();

            ans.push_back(idx);

            // Mark server as busy
            busyServers.push({time + tasks[i], idx});
        }

        return ans;
    }
};
