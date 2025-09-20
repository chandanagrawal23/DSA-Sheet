#include <bits/stdc++.h>
using namespace std;

class Router
{
public:
    int cap;
    queue<vector<int>> q;                        // FIFO packets
    set<vector<int>> seen;                       // detect duplicates
    unordered_map<int, vector<int>> times;       // dest -> timestamps
    unordered_map<int, int> removed;             // dest -> how many to skip

    Router(int memoryLimit)
    {
        cap = memoryLimit;
    }

    bool addPacket(int src, int dst, int ts)
    {
        vector<int> pkt = {src, dst, ts};
        if (seen.count(pkt)) return false;

        if (q.size() == cap) // evict oldest
        {
            auto old = q.front();
            q.pop();
            seen.erase(old);
            removed[old[1]]++;   // mark one timestamp as removed
        }

        q.push(pkt);
        seen.insert(pkt);
        times[dst].push_back(ts);  // append timestamp
        return true;
    }

    vector<int> forwardPacket()
    {
        if (q.empty()) return {};
        auto pkt = q.front();
        q.pop();
        seen.erase(pkt);
        removed[pkt[1]]++;        // mark removed
        return pkt;
    }

    int getCount(int dst, int l, int r)
    {
        if (!times.count(dst)) return 0;

        auto &arr = times[dst];        // timestamps list
        int skip = removed[dst];       // how many to ignore from front

        // valid timestamps are in arr[skip ... end)
        auto it1 = lower_bound(arr.begin() + skip, arr.end(), l);
        auto it2 = upper_bound(arr.begin() + skip, arr.end(), r);

        return int(it2 - it1);
    }
};

/*
APPROACH SECTION
----------------
1. Data Structures Used:
   - queue<vector<int>> q:
       Maintains packets in FIFO order, required for eviction when memory is full.
   - set<vector<int>> seen:
       Used to detect duplicates (O(log N) lookup).
   - unordered_map<int, vector<int>> times:
       For each destination, stores timestamps of all packets ever inserted.
   - unordered_map<int, int> removed:
       Tracks how many packets for a given destination have been removed/evicted,
       so we can "skip" them logically without deleting from vector<int>.

2. addPacket(src, dst, ts):
   - Rejects packet if already seen.
   - If memory capacity reached, evicts oldest packet (from queue).
   - Updates "removed" counter for its destination to mark it logically deleted.
   - Appends timestamp into `times[dst]` for later queries.

3. forwardPacket():
   - Pops oldest packet from queue.
   - Marks it removed in "seen" and increments "removed" counter for that destination.
   - Returns the packet.

4. getCount(dst, l, r):
   - Looks at timestamps list for given destination.
   - Skips the first `removed[dst]` timestamps (which are logically deleted).
   - Performs binary search (lower_bound/upper_bound) to count how many timestamps lie in [l, r].
   - Result = number of valid packets in that time range.

5. Why "removed" is needed:
   - Because we never erase from `times[dst]` (costly), we just maintain a counter of how many
     from the front are logically removed. This makes getCount efficient.

Time Complexity:
- addPacket : O(log N) [due to set insert/erase]  
- forwardPacket : O(log N) [due to set erase]  
- getCount : O(log M) where M = number of timestamps stored for that destination (binary search).  

Space Complexity:
- O(N + total_timestamps)  
  where N = capacity of router (queue + set), and total_timestamps is all inserted
  timestamps across destinations.

----------------
DRY RUN EXAMPLE
----------------
Router rt(3);  // capacity = 3

Step 1: rt.addPacket(1,5,1)
Queue: [(1,5,1)], times[5]: [1], removed[5]:0

Step 2: rt.addPacket(2,5,3)
Queue: [(1,5,1),(2,5,3)], times[5]: [1,3], removed[5]:0

Step 3: rt.addPacket(3,5,4)
Queue: [(1,5,1),(2,5,3),(3,5,4)], times[5]: [1,3,4], removed[5]:0

Step 4: rt.addPacket(4,5,7)  // capacity full, evict oldest (1,5,1)
Queue: [(2,5,3),(3,5,4),(4,5,7)], times[5]: [1,3,4,7], removed[5]:1

Step 5: rt.getCount(5,2,8)
- valid timestamps = [3,4,7] (skip first 1)
- Count = 3

Step 6: rt.forwardPacket() -> removes (2,5,3)
Queue: [(3,5,4),(4,5,7)], removed[5]:2

Step 7: rt.getCount(5,2,8)
- valid timestamps = [4,7] (skip first 2)
- Count = 2

// This demonstrates how 'removed' tracks logically deleted packets without physically erasing from vector.

*/
