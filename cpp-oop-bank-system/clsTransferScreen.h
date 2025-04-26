#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen :protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber(string message)
    {
        string AccountNumber = "";
        cout << message;
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t   Transfer Screen");

        string AccountNumberFrom = _ReadAccountNumber("\nPlease Enter Account Number to Transform From ? ");

        while (!clsBankClient::IsClientExist(AccountNumberFrom))
        {
            cout << "\nClient with [" << AccountNumberFrom << "] does not exist.\n";
            AccountNumberFrom = _ReadAccountNumber("\nPlease Enter Account Number to Transform From ? ");
        }

        clsBankClient ClientFrom = clsBankClient::Find(AccountNumberFrom);
        _PrintClient(ClientFrom);

        string AccountNumberTo = _ReadAccountNumber("\nPlease Enter Account Number to Transform To ? ");

        while (!clsBankClient::IsClientExist(AccountNumberTo))
        {
            cout << "\nClient with [" << AccountNumberTo << "] does not exist.\n";
            AccountNumberTo = _ReadAccountNumber("\nPlease Enter Account Number to Transform To ? ");
        }

        clsBankClient ClientTo = clsBankClient::Find(AccountNumberTo);
        _PrintClient(ClientTo);


        double Amount = 0;
        cout << "\nPlease enter Transfer amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        if (Amount > ClientFrom.AccountBalance)
        {
            cout << "\nCannot transfer, Insuffecient Balance!\n";
            cout << "\nAmout to transfer is: " << Amount;
            cout << "\nYour Balance is: " << ClientFrom.AccountBalance;
            return;
        }

        cout << "\nAre you sure you want to transform this amount? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (ClientFrom.Withdraw(Amount))
            {
                ClientTo.Deposit(Amount);
                cout << "\nAmount Transferred Successfully.\n";
                _PrintClient(ClientFrom);
                _PrintClient(ClientTo);

            }
            else
            {
                cout << "\nOperation was cancelled.\n";
            }

        }

    };

};