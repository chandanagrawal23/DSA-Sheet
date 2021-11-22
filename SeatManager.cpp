//https://leetcode.com/problems/seat-reservation-manager/
class SeatManager {
public:
    priority_queue<int,vector<int>,greater<int>>pq; //create min heap
	SeatManager(int n) {
		for(int i=1;i<=n;++i)
			pq.push(i);
	}

	int reserve() {
		int reserve_seat=pq.top(); //Remove the top element from min heap and reserve the seat
		pq.pop();
		return reserve_seat;
	}

	void unreserve(int seatNumber) {
		pq.push(seatNumber); //push back the unreserve seat into heap
	}
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
