class Solution
{
public:
    string simplifyPath(string path)
    {
        vector<string> stack;
        int len = path.size();
        string dir;

        for (int i = 0; i < len; i++)
        {
            if (path[i] == '/')
                continue; // Skip redundant slashes

            dir = "";
            while (i < len && path[i] != '/')
            {
                dir += path[i++];
            }

            if (dir == ".")
                continue; // Ignore current directory

            if (dir == "..")
            {
                if (!stack.empty())
                    stack.pop_back(); // Go up one directory
            }
            else
            {
                stack.push_back(dir); // Add valid directory
            }
        }

        string result;
        for (const string &d : stack)
        {
            result += "/" + d;
        }

        return result.empty() ? "/" : result;
    }
};

/*
Approach:
- Split the path by '/'
- Use a stack to process each part:
  - Skip "." and empty
  - Pop for ".."
  - Push valid directory names
- Join the stack to form the simplified absolute path

Time: O(n), where n = length of the path
Space: O(n), for storing valid path parts
*/
