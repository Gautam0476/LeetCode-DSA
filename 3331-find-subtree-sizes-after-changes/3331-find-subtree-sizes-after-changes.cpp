class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent(n, -1);
        vector<int> last(26, -1);
        vector<int> prev(n, -1);

        // DFS on original tree
        stack<pair<int, bool>> st;
        st.push({0, true});

        while (!st.empty()) {
            auto [u, enter] = st.top();
            st.pop();

            int c = s[u] - 'a';

            if (enter) {
                prev[u] = last[c];

                if (u == 0)
                    newParent[u] = -1;
                else
                    newParent[u] = (last[c] != -1)
                                   ? last[c] : parent[u];

                last[c] = u;

                st.push({u, false});

                for (int i = adj[u].size() - 1; i >= 0; i--) {
                    st.push({adj[u][i], true});
                }
            }
            else {
                last[c] = prev[u];
            }
        }

        // Build modified tree
        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        // Calculate subtree sizes
        vector<int> order;
        stack<int> dfs;
        dfs.push(0);

        while (!dfs.empty()) {
            int u = dfs.top();
            dfs.pop();

            order.push_back(u);

            for (int v : tree[u]) {
                dfs.push(v);
            }
        }

        vector<int> ans(n, 1);

        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];

            if (newParent[u] != -1) {
                ans[newParent[u]] += ans[u];
            }
        }

        return ans;
    }
};