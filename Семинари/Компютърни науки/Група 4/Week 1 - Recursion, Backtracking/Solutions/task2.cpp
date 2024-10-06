class Solution {
public:
    
    void readBinaryWatchUtil(bool arr[10], bool state, int idx, int toTurnOn, vector<string>& result)
    {
        if(toTurnOn == 0 && state == false)
        {
            string str = "";
            int hours = 0, minutes = 0;
            int tmp = 1;
            for(int i = 3; i>=0; i--)
            {
                hours += arr[i]*tmp;
                tmp*=2;
            }
            if(hours < 10)
            {
                str.push_back(hours + '0');
            }
            else
            {
                str.push_back(hours / 10 + '0');
                str.push_back(hours%10 + '0');
            }
            str.push_back(':');
            tmp = 1;
            for(int i = 9; i>=4; i--)
            {
                minutes += arr[i]*tmp;
                tmp*=2;
            }
            str.push_back(minutes / 10 + '0');
            str.push_back(minutes % 10 + '0');
            if(hours >= 12 || minutes >= 60)
            return;
            result.push_back(str);
            return;
            
        }  
        if(idx >= 10 || (toTurnOn == 0 && state == true))
        {
            return;
        }
        arr[idx] = state;
        readBinaryWatchUtil(arr,true,idx+1,toTurnOn-state,result);
        readBinaryWatchUtil(arr,false,idx+1,toTurnOn-state,result);
        arr[idx] = 0;

    }
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> result;
        bool arr[10];
        readBinaryWatchUtil(arr,true,0,turnedOn,result);
        readBinaryWatchUtil(arr,false,0,turnedOn,result);
        reverse(result.begin(), result.end());
        return result;
    }
};