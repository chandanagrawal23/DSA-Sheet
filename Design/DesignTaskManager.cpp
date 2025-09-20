#include <bits/stdc++.h>
using namespace std;

class TaskManager {
private:
    struct Task {
        int userId;
        int taskId;
        int priority;
    };

    unordered_map<int, Task> mp;       // taskId -> Task
    set<array<int, 3>> st;             // {-priority, -taskId, userId} for ordering

public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto& task : tasks) {
            add(task[0], task[1], task[2]);
        }
    }

    void add(int userId, int taskId, int priority) {
        mp[taskId] = {userId, taskId, priority};
        st.insert({-priority, -taskId, userId});  // max-heap like ordering using set
    }

    void edit(int taskId, int newPriority) {
        if (mp.find(taskId) == mp.end()) return;
        Task& task = mp[taskId]; 
        st.erase({-task.priority, -task.taskId, task.userId});
        task.priority = newPriority;
        st.insert({-newPriority, -taskId, task.userId});
    }

    void rmv(int taskId) {
        if (mp.find(taskId) == mp.end()) return;
        Task& task = mp[taskId]; 
        st.erase({-task.priority, -task.taskId, task.userId});
        mp.erase(taskId);
    }

    int execTop() {
        while (!st.empty()) {
            auto topTask = *st.begin();
            int userId = topTask[2];
            int taskId = -topTask[1];

            if (mp.find(taskId) != mp.end()) {
                st.erase(topTask);
                mp.erase(taskId);
                return userId;
            } else {
                st.erase(topTask);  // stale task removed
            }
        }
        return -1;
    }
};

/*
APPROACH SECTION
----------------
1. Data Structures Used:
   - unordered_map<int, Task> mp:
       Maps taskId to Task structure for O(1) access, edit, and deletion.
   - set<array<int,3>> st:
       Stores tasks ordered by priority descending, then taskId descending (to break ties),
       then userId. Using -priority and -taskId to simulate max-heap behavior in set.

2. Constructor TaskManager(tasks):
   - Iterates over given tasks and adds them to mp and st.

3. add(userId, taskId, priority):
   - Insert into mp.
   - Insert into st as {-priority, -taskId, userId} for ordering.

4. edit(taskId, newPriority):
   - Lookup task in mp.
   - Remove old entry from st.
   - Update priority in mp.
   - Insert new entry in st.

5. rmv(taskId):
   - Lookup task in mp.
   - Remove entry from st.
   - Remove from mp.

6. execTop():
   - Returns userId of task with highest priority (and highest taskId if tie).
   - If task is already removed from mp (stale in st), erase and continue.
   - Remove executed task from mp and st.

Time Complexity:
- add: O(log N) due to set insertion
- edit: O(log N) for erase + O(log N) for insert
- rmv: O(log N) for set erase
- execTop: O(log N) per executed task (may remove stale tasks)

Space Complexity:
- O(N), storing all active tasks in mp and st

----------------
DRY RUN EXAMPLE
----------------
Initial Tasks: [[1,101,5],[2,102,3],[1,103,5]]

Step 1: Constructor
mp:
  101 -> {1,101,5}
  102 -> {2,102,3}
  103 -> {1,103,5}
st (ordered by -priority, -taskId):
  {(-5,-103,1), (-5,-101,1), (-3,-102,2)}  // highest priority first, tie broken by higher taskId

Step 2: execTop()
- top = (-5,-103,1) -> taskId=103, userId=1
- Remove 103 from mp and st
- Return 1

Step 3: edit(101,6)
- Remove (-5,-101,1) from st
- Update mp[101].priority = 6
- Insert (-6,-101,1) into st
- st now: {(-6,-101,1), (-3,-102,2)}

Step 4: execTop()
- top = (-6,-101,1) -> taskId=101, userId=1
- Remove from mp and st
- Return 1

Step 5: rmv(102)
- Remove (-3,-102,2) from st and mp

Step 6: execTop()
- st empty, return -1

// Demonstrates how set maintains ordering by priority and taskId, and how stale tasks are ignored.
*/
