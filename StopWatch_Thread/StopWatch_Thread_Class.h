class StopWatch
{
    private:
        int hours;
        int minutes;
        int seconds;
        int miliseconds;
        int hours2;
        int minutes2;
        int seconds2;
        int miliseconds2;
        int Record_Count;

    public:
        bool isStop;
        bool isStop2;
        void IncreaseHour()
        {
            hours++;
        }
        void IncreaseMinute()
        {
            if (minutes > 59)
            {
                minutes = 0;
                IncreaseHour();
            }
            else
            {
                minutes++;
            }
        }
        void IncreaseSec()
        {
            if (seconds > 59)
            {
                seconds = 0;
                IncreaseMinute();
            }
            else
            {
                seconds++;
            }
        }
        void IncreaseMilisec()
        {
            if(miliseconds > 99)
            {
                miliseconds = 0;
                IncreaseSec();
            }
            else
            {
                miliseconds++;
            }
        }
        void IncreaseHour2()
        {
            hours2++;
        }
        void IncreaseMinute2()
        {
            if (minutes2 > 59)
            {
                minutes2 = 0;
                IncreaseHour2();
            }
            else
            {
                minutes2++;
            }
        }
        void IncreaseSec2()
        {
            if (seconds2 > 59)
            {
                seconds2 = 0;
                IncreaseMinute2();
            }
            else
            {
                seconds2++;
            }
        }
        void IncreaseMilisec2()
        {
            if (miliseconds > 99)
            {
                miliseconds2 = 0;
                IncreaseSec2();
            }
            else
            {
                miliseconds2++;
            }
        }
        void Start_Click()
        {
            isStop = false;
            isStop2 = false;
        }
        void Stop_Click()
        {
            isStop = true;
            isStop2 = true;
        }
        void Reset_Click()
        {
            hours = 0;
            minutes = 0;
            seconds = 0;
            miliseconds = 0;
            hours2 = 0;
            minutes2 = 0;
            seconds2 = 0;
            miliseconds2 = 0;
            Record_Count = 0;
            isStop = true;
            isStop2 = true;
        }
        void Record_Click()
        {
            hours2 - 0;
            minutes2 = 0;
            seconds2 = 0;
            miliseconds2 =0;
        }
        void IncreaseRecordCount()
        {
            Record_Count++;
        }
        int GetRecordCount()
        {
            return Record_Count;
        }
        int GetHours()
        {
            return hours;
        }
        int GetHours2()
        {
            return hours2;
        }
        int GetMinutes()
        {
            return minutes;
        }
        int GetMinutes2()
        {
            return minutes2;
        }
       int GetSeconds()
        {
            return seconds;
        }
        int GetSeconds2()
        {
            return seconds2;
        }
        int GetMiliseconds()
        {
            return miliseconds;
        }
        int GetMiliseconds2()
        {
            return miliseconds2;
        }
};
