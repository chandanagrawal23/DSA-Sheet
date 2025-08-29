// Approach 1 : Sweep Line + 1 multiset , O(N*K) in worst case)
// Learn this first and then learn approach 2

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int day;
    int knowledge;
    bool isStart; // true = start of meeting, false = end of meeting
};

// Custom comparator for sorting events
bool compareEvents(const Event &a, const Event &b) {
    if (a.day == b.day)
        return a.isStart > b.isStart; // start events before end events
    return a.day < b.day;
}

int getMaxKnowledge(int d, int n, const vector<int> &s,
                    const vector<int> &e, const vector<int> &a, int k) {
    // <day, knowledge, isStart>
    vector<Event> events;
    

    // Convert each meeting into two events: start and end+1
    for (int i = 0; i < n; i++) {
        events.push_back({s[i], a[i], true});      // start of meeting
        events.push_back({e[i] + 1, a[i], false}); // meeting ends after e[i]
    }

    // Sort events by day (start events come before end events on same day)
    sort(events.begin(), events.end(), compareEvents);

    multiset<int> active;  // active meetings’ knowledge values
    int maxKnowledge = 0;

    // Process events
    for (int i = 0; i < (int)events.size();) 
    {
        int currentDay = events[i].day;

        // Process all events for this day
        while (i < (int)events.size() && events[i].day == currentDay) 
        {
            if (events[i].isStart)
                active.insert(events[i].knowledge); // add meeting knowledge
            else
                active.erase(active.find(events[i].knowledge)); // remove ended meeting
            i++;
        }

        // Pick top-k knowledge values from active in descending order
        // tht is why see I use "rbegin" not "begin"
        int sum = 0, count = 0;
        for (auto it = active.rbegin(); it != active.rend() && count < k; ++it, ++count) 
        {
            sum += *it;
        }

        maxKnowledge = max(maxKnowledge, sum);
    }

    return maxKnowledge;
}

// Main function with test cases
int main() {
    // Test Case 1: Provided example
    {
        int d = 10, n = 4, k = 2;
        vector<int> s = {2, 5, 4, 3};
        vector<int> e = {8, 9, 7, 5};
        vector<int> a = {800, 1600, 200, 400};
        cout << "Test Case 1 Output: " << getMaxKnowledge(d, n, s, e, a, k) << endl; // Expected: 2400
    }

    // Test Case 2: Custom case with overlaps and duplicates
    {
        int d = 7, n = 6, k = 3;
        vector<int> s = {1, 2, 2, 3, 3, 4}; // Start days
        vector<int> e = {5, 4, 3, 5, 4, 5}; // End days
        vector<int> a = {100, 200, 200, 300, 100, 400}; // Knowledge values
        cout << "Test Case 2 Output: " << getMaxKnowledge(d, n, s, e, a, k) << endl; // Expected: 900
    }

    return 0;
}

/*
Approach:
1. Break each meeting into start and end+1 events.
2. Sort events by day (start before end if same day).
3. Maintain a multiset of active meeting knowledge values.
4. For each day, take the top k from active and update max sum.

Time:  O(n log n + n*k) worst case
Space: O(n)
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Approach 2 : Sweep Line + 2 multiset , O(N*logN)
#include <bits/stdc++.h>
using namespace std;

// Event structure for meeting start/end
struct Event {
    int day, knowledge;
    bool isStart;
};

// Sort events by day, start events before end events
bool compareEvents(const Event &a, const Event &b) {
    if (a.day == b.day) return a.isStart > b.isStart;
    return a.day < b.day;
}

// Insert knowledge into topK or rest, update sumTopK
void handleInsert(int knowledge, multiset<int, greater<int>> &topK, multiset<int, greater<int>> &rest, long long &sumTopK, int k) {
    if (topK.size() < k) { // Room in topK
        topK.insert(knowledge);
        sumTopK += knowledge;
    } else {
        auto smallestTopK = topK.rbegin(); // Smallest in topK
        if (knowledge > *smallestTopK) {
            sumTopK += knowledge - *smallestTopK; // Replace smallest
            rest.insert(*smallestTopK); // Move smallest to rest
            topK.erase(prev(topK.end()));
            topK.insert(knowledge);
        } else {
            rest.insert(knowledge); // Add to rest
        }
    }
}

// Remove knowledge from topK or rest, update sumTopK
void handleRemove(int knowledge, multiset<int, greater<int>> &topK, multiset<int, greater<int>> &rest, long long &sumTopK, int k) {
    auto itTopK = topK.find(knowledge);
    if (itTopK != topK.end()) { // Found in topK
        sumTopK -= knowledge;
        topK.erase(itTopK);
        if (!rest.empty()) { // Promote largest from rest
            auto largestRest = rest.begin();
            sumTopK += *largestRest;
            topK.insert(*largestRest);
            rest.erase(largestRest);
        }
    } else { // Check rest
        auto itRest = rest.find(knowledge);
        if (itRest != rest.end()) {
            rest.erase(itRest); // Remove from rest
        }
    }
}

// Compute max knowledge from k meetings per day
int getMaxKnowledge(int d, int n, const vector<int> &s, const vector<int> &e, const vector<int> &a, int k) {
    if (k == 0 || n == 0) return 0; // Handle edge cases

    vector<Event> events;
    events.reserve(2 * n); // Pre-allocate for efficiency
    for (int i = 0; i < n; i++) {
        events.push_back({s[i], a[i], true}); // Start event
        events.push_back({e[i] + 1, a[i], false}); // End event
    }

    sort(events.begin(), events.end(), compareEvents); // Sort events

    multiset<int, greater<int>> topK, rest; // topK: top k values, rest: others
    long long sumTopK = 0; // Sum of top k values
    int maxKnowledge = 0; // Max knowledge observed

    for (int i = 0; i < (int)events.size();) {
        int currentDay = events[i].day;
        while (i < (int)events.size() && events[i].day == currentDay) { // Process all events for day
            if (events[i].isStart) {
                handleInsert(events[i].knowledge, topK, rest, sumTopK, k);
            } else {
                handleRemove(events[i].knowledge, topK, rest, sumTopK, k);
            }
            i++;
        }
        maxKnowledge = max(maxKnowledge, (int)sumTopK); // Update max
    }

    return maxKnowledge;
}

// Main function with test cases
int main() {
    // Test Case 1: Provided example
    {
        int d = 10, n = 4, k = 2;
        vector<int> s = {2, 5, 4, 3};
        vector<int> e = {8, 9, 7, 5};
        vector<int> a = {800, 1600, 200, 400};
        cout << "Test Case 1 Output: " << getMaxKnowledge(d, n, s, e, a, k) << endl; // Expected: 2400
    }

    // Test Case 2: Custom case with overlaps and duplicates
    {
        int d = 7, n = 6, k = 3;
        vector<int> s = {1, 2, 2, 3, 3, 4}; // Start days
        vector<int> e = {5, 4, 3, 5, 4, 5}; // End days
        vector<int> a = {100, 200, 200, 300, 100, 400}; // Knowledge values
        cout << "Test Case 2 Output: " << getMaxKnowledge(d, n, s, e, a, k) << endl; // Expected: 900
    }

    return 0;
}

/*
Approach:
1. Event Creation: For each meeting i, create two events:
    - Start event at day s[i] with knowledge a[i].
    - End event at day e[i]+1 with knowledge a[i] (since e[i] is inclusive).
    This results in 2n events, stored in a vector.

2. Sort Events: Sort events by day, with start events before end events on the same day, to process the timeline chronologically.

3. Two Multisets:
    - Use two multisets (both in descending order):
     - topK: Stores the k largest knowledge values of active meetings.
     - rest: Stores the remaining active knowledge values.
    - Maintain sumTopK as the sum of values in topK, representing the knowledge from the k best meetings on the current day.

4. Event Processing (Line Sweep):
    - Iterate through sorted events, processing all events for each day.
    - For a start event (knowledge value v):
     - If topK has fewer than k elements, insert v into topK and add v to sumTopK.
     - Otherwise, if v is larger than the smallest in topK, replace the smallest (move it to rest), insert v into topK, and update sumTopK.
     - If v is smaller, insert it into rest.
    - For an end event (knowledge value v):
     - If v is in topK, remove it, subtract v from sumTopK, and if rest is non-empty, promote the largest from rest to topK, adding it to sumTopK.
     - If v is in rest, remove it.
    - After processing each day’s events, update maxKnowledge with sumTopK.

5. Edge Cases:
    - If k=0 or n=0, return 0 (no meetings can be attended or no meetings exist).
    - Handle duplicate knowledge values using multiset (find and erase one instance).
    - Ensure correct handling when more than k meetings are active.

Time Complexity:
- Event creation: O(n).
- Sorting 2n events: O(n log n).
- Processing 2n events, each with O(log n) multiset operations (insert, erase, find): O(n log n).
- Total: O(n log n).

Space Complexity:
- Events vector: O(n) for 2n events.
- Multisets topK (up to k elements) and rest (up to n elements): O(n).
- Total: O(n).

*/
