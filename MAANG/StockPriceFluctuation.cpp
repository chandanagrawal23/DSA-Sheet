class StockPrice
{
public:
    map<int, int> record;          // mapping of timestamp -> price
    multiset<int> prices;          // store all prices for min/max queries, asceding order

    void update(int timestamp, int price)
    {
        // if timestamp already exists, remove old price first
        if (record.find(timestamp) != record.end())
            prices.erase(prices.find(record[timestamp])); // if I do prices.erase(record[timestamp]) , it will delete all occurence

        record[timestamp] = price;
        prices.insert(price);
    }

    int current()
    {
        return record.rbegin()->second; // latest timestamp
    }

    int maximum()
    {
        return *prices.rbegin(); // highest price
    }

    int minimum()
    {
        return *prices.begin(); // lowest price
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */


/*

Approach:
==============
1. Maintain a map<timestamp, price> for direct timestamp access.
   - Map keeps timestamps sorted automatically.
2. Maintain a multiset of all prices to get min and max in O(1).
3. On update():
   - If timestamp already exists, remove its old price from multiset.
   - Insert the new price.
4. current(): return price of latest timestamp (last in map).
5. maximum()/minimum(): return highest and lowest element from multiset.

Time Complexity:
- update(): O(log n)
- current(): O(1)
- maximum()/minimum(): O(1)

Space Complexity: O(n)
*/
