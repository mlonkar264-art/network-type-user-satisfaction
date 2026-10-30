#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

int main()
{
    const int R = 3, C = 3;
    string network[R] = {"4G", "5G", "WiFi"};
    string satisfaction[C] = {
        "Satisfied", "Neutral", "Dissatisfied"
    };

    int freq[R][C] = {0};
    int rowTotal[R] = {0};
    int colTotal[C] = {0};
    int total = 0;

    cout << "\n";
    cout << "============================================================\n";
    cout << "       NETWORK TYPE AND USER SATISFACTION ANALYSIS\n";
    cout << "============================================================\n";

    int n;
    cout << "\nEnter total number of users: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "\nError: Number of users must be positive.\n";
        return 0;
    }

    cout << "\nNETWORK TYPE: 1 = 4G, 2 = 5G, 3 = WiFi\n";
    cout << "SATISFACTION: 1 = Satisfied, 2 = Neutral, "
         << "3 = Dissatisfied\n";
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        int net, sat;

        cout << "\nUser " << i + 1 << "\n";
        cout << "Enter network type (1-3): ";
        cin >> net;
        cout << "Enter satisfaction (1-3): ";
        cin >> sat;

        if (net < 1 || net > 3 || sat < 1 || sat > 3)
        {
            cout << "Invalid input! Enter values between 1 and 3.\n";
            i--;
            continue;
        }

        freq[net - 1][sat - 1]++;
    }

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            rowTotal[i] += freq[i][j];
            colTotal[j] += freq[i][j];
            total += freq[i][j];
        }
    }

    // Frequency report
    cout << "\n\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                    FREQUENCY REPORT                      |\n";
    cout << "+----------------------------------------------------------+\n";

    cout << left << setw(12) << "Network"
         << setw(15) << "Satisfied"
         << setw(12) << "Neutral"
         << setw(16) << "Dissatisfied"
         << setw(8) << "Total" << "\n";

    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < R; i++)
    {
        cout << left << setw(12) << network[i];

        for (int j = 0; j < C; j++)
            cout << setw(j == 2 ? 16 : (j == 0 ? 15 : 12))
                 << freq[i][j];

        cout << rowTotal[i] << "\n";
    }

    cout << "------------------------------------------------------------\n";
    cout << left << setw(12) << "Total";

    for (int j = 0; j < C; j++)
        cout << setw(j == 2 ? 16 : (j == 0 ? 15 : 12))
             << colTotal[j];

    cout << total << "\n";

    // Percentage report
    cout << "\n\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                   PERCENTAGE REPORT                      |\n";
    cout << "+----------------------------------------------------------+\n";

    cout << left << setw(12) << "Network"
         << setw(15) << "Satisfied"
         << setw(12) << "Neutral"
         << setw(16) << "Dissatisfied" << "\n";

    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < R; i++)
    {
        cout << left << setw(12) << network[i];

        for (int j = 0; j < C; j++)
        {
            double p = freq[i][j] * 100.0 / total;
            cout << fixed << setprecision(2)
                 << setw(j == 2 ? 16 : (j == 0 ? 15 : 12))
                 << p;
        }
        cout << "\n";
    }

    // Chi-square calculation
    double chi = 0;
    bool valid = true;

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            double expected =
                (double)rowTotal[i] * colTotal[j] / total;

            if (expected < 5)
                valid = false;

            if (expected > 0)
            {
                double d = freq[i][j] - expected;
                chi += d * d / expected;
            }
        }
    }

    cout << "\n\n";
    cout << "+----------------------------------------------------------+\n";
    cout << "|                  CHI-SQUARE TEST                         |\n";
    cout << "+----------------------------------------------------------+\n";

    cout << "  Chi-square statistic : " << fixed << setprecision(4)
         << chi << "\n";
    cout << "  Degrees of freedom   : 4\n";
    cout << "  Significance level   : 0.05\n";
    cout << "  Critical value       : 9.488\n";

    cout << "------------------------------------------------------------\n";

    if (!valid)
        cout << "  WARNING: Some expected frequencies are below 5.\n";

    if (chi > 9.488)
    {
        cout << "  DECISION: Reject the null hypothesis.\n";
        cout << "  CONCLUSION: Significant association found.\n";
    }
    else
    {
        cout << "  DECISION: Fail to reject the null hypothesis.\n";
        cout << "  CONCLUSION: Insufficient evidence of association.\n";
    }

    cout << "============================================================\n";
    cout << "                 END OF STATISTICAL REPORT\n";
    cout << "============================================================\n";

    return 0;
}
     