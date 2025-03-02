#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

bool compareJobs(const pair<long long, long long>& job1, const pair<long long, long long>& job2) {
    if (job1.second != job2.second)
        return job1.second < job2.second;

    return job1.first > job2.first;
}

int main() {
    int l;
    cin >> l;

    vector<pair<long long, long long> > jobs(l);

    for (int i = 0; i < l; ++i) {
        cin >> jobs[i].first >> jobs[i].second;
    }
    
    sort(jobs.begin(), jobs.end(), compareJobs);
    
    // Initialize variables for the simulation
    long long current_time = 0;  // Tracks the total time spent on jobs
    long long total_money = 0;   // Tracks the total money earned or lost

    // Process each job
    for (int i = 0; i < l; ++i) {
        long long duration = jobs[i].first;
        long long deadline = jobs[i].second;

        // Update current time by adding the job duration
        current_time += duration;

        // Compute the difference between the deadline and the current time
        long long difference = deadline - current_time;

        // Update total_money based on how early or late the job was completed
        total_money += difference;
    }

    // Output the final total money
    cout << total_money << endl;

    return 0;

    // for (int i = 0; i < l; ++i) {
    //     cout << jobs[i].first << " " << jobs[i].second << endl;
    // }
}