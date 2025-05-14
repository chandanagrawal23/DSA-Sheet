class TopVotedCandidate 
{
public:
    // Store the times of each vote
    vector<int> times;

    // Store the leading candidate at each time
    vector<int> leadingAtTime;

    TopVotedCandidate(vector<int>& persons, vector<int>& times) 
    {
        // Initialize the times vector
        this->times = times;

        // Map to count votes per person
        unordered_map<int, int> voteCount;

        int leader = -1;
        int maxVotes = 0;

        // Traverse through all votes
        for (int i = 0; i < persons.size(); ++i) 
        {
            voteCount[persons[i]]++;

            // Update leader if current person has max or equal votes
            // If tie, the most recent vote wins
            if (voteCount[persons[i]] >= maxVotes) 
            {
                leader = persons[i];
                maxVotes = voteCount[persons[i]];
            }

            // Store the leader at this point in time
            leadingAtTime.push_back(leader);
        }
    }

    int q(int t) 
    {
        int left = 0, right = times.size() - 1;
        int index = -1;

        // Binary search to find the greatest times[i] <= t
        while (left <= right) 
        {
            int mid = left + (right - left) / 2;

            if (times[mid] <= t) 
            {
                index = mid;        // valid candidate
                left = mid + 1;     // try to find a later valid time
            } 
            else 
            {
                right = mid - 1;
            }
        }

        // Return the leader at the found time
        return leadingAtTime[index];
    }
};


/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */
