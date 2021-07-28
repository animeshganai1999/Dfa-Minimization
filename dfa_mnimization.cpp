#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
    Name = Animesh Ganai
    Roll = 20, semester = 6
    code = minimization of DFA
*/
/*
    Assumptions:
        1. finite state of symbols {0,1}
*/
int main()
{
    int v, e, starting_state, i, j, y, F;
    // v = Number of vertices , e = Number of edges
    std::cout << "Consider states are starts from 0" << std::endl;
    std::cout << "Enter Number of States : ";
    std::cin >> v;
    std::cout << "Enter starting State : ";
    cin >> starting_state;
    std::vector<int> adjInp0(v, -1); // adjancency matrix
    std::vector<int> adjInp1(v, -1);
    vector<int> final_state; // list of final states
    std::cout << "Enter Number of Final states : ";
    cin >> F;
    std::cout << "Enter all final states : ";
    for (i = 0; i < F; i++)
    {
        cin >> y;
        final_state.push_back(y);
    }

    e = 2 * v;
    //   taking input for state transition diagram
    std::cout << "Enter current_state symbol next_state " << std::endl;
    for (i = 0; i < v; i++)
    {
        std::cout << "enter the next state from state " << i << " by taking 0 : ";
        std::cin >> y;
        adjInp0[i] = y;

        std::cout << "enter the next state from state " << i << " by taking 1 : ";
        std::cin >> y;
        adjInp1[i] = y;
    }
    //  --------------------------------------------------- INITIALIZATION COMPLETE--------------------------------------
    vector<int> final_nonfinal(v, 0);
    // 0 ---->> nonfinal states, 1 ----->> final states
    for (i = 0; i < final_state.size(); i++)
    {
        final_nonfinal[final_state[i]] = 1;
    }

    int table[v][v];

    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            if (j < i)
            {
                table[i][j] = 0;
            }
            else
            {
                table[i][j] = -1;
            }
        }
    }
    int iteration = 0, flag;
    int max0, min0, max1, min1;
    while (true)
    {
        flag = 0;
        for (i = 1; i < v; i++)
        {
            for (j = 0; j < i; j++)
            {

                if ((iteration == 0) && (final_nonfinal[i] != final_nonfinal[j]))
                {
                    table[i][j] = 1;
                    flag = 1;
                }
                else
                {
                    if ((adjInp0[i] != adjInp0[j]) || (adjInp1[i] != adjInp1[j]))
                    {
                        max0 = max(adjInp0[i], adjInp0[j]);
                        min0 = min(adjInp0[i], adjInp0[j]);
                        max1 = max(adjInp1[i], adjInp1[j]);
                        min1 = min(adjInp1[i], adjInp1[j]);
                        if ((table[max0][min0] == 1) || (table[max1][min1] == 1))
                        {
                            if (table[i][j] == 0)
                            {
                                table[i][j] = 1;
                                flag = 1;
                            }
                        }
                    }
                }
            }
        }
        iteration++;
        if (flag == 0)
        {
            break;
        }
    }

    int index = 1, val;
    vector<int> result(v, -1);
    for (i = 1; i < v; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (table[i][j] == 0)
            {
                if (result[i] == -1 && result[j] == -1)
                {
                    result[i] = index;
                    result[j] = index;
                    index++;
                }
                else
                {
                    if (result[i] != -1 || result[j] != -1)
                    {
                        val = max(result[i], result[j]);
                        result[i] = val;
                        result[j] = val;
                    }
                }
            }
        }
    }
    int number_of_state = 0;
    for (i = 0; i < v; i++)
    {
        if (result[i] == -1)
        {
            number_of_state++;
        }
    }
    int arr_size = index + number_of_state;
    std::vector<int> final_dfa[arr_size];
    int push_after = index;

    for (i = 0; i < v; i++)
    {
        if (result[i] == -1)
        {
            final_dfa[push_after].push_back(i);
            push_after++;
        }
        else
        {
            final_dfa[result[i]].push_back(i);
        }
    }
    number_of_state += (index - 1);
    std::cout << "Number of states in minimal DFA : " << number_of_state << endl;
    cout << "The states are : " << endl;
    for (i = 1; i < arr_size; i++)
    {
        cout << "(";
        for (j = 0; j < final_dfa[i].size(); j++)
        {
            std::cout << final_dfa[i][j] << ",";
        }
        cout << ")";
        std::cout << "   ";
    }
    return 0;
}