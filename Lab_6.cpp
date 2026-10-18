#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <vector>
#include <sstream>
#include <limits>
#include <fstream>
using namespace std;

int main()
{
    cout << fixed << setprecision(2);

    double grandTotalSales = 0.0;
    int totalCustomers = 0;
    const vector<string> inventoryNames = { "Cheese Pizza", "Pepperoni Pizza", "Turkey Sandwich", "Salad" };
    const vector<int> startingInventory = { 20, 5, 8, 12 };
    vector<int> remainingInventory = startingInventory;

    while (true) {
        // per-customer data
        string customerName;
        cout << "\nEnter customer name: ";
        getline(cin, customerName);

        // If previous input left a newline, ensure we actually get a name
        if (customerName.empty()) {
            getline(cin, customerName);
        }

        vector<string> cartNames;
        vector<int> cartQuantities;
        vector<double> cartUnitPrices;

        ostringstream receiptAccumulator;

        double subtotal = 0.0;

        // Menu loop: user can select multiple items until they choose Checkout
        while (true) {
            cout << "\nPlease select from the following options:" << endl
                << "Food Item " << setw(20) << "Small (s)" << setw(15) << "Medium (m)" << setw(15) << "Large (l)" << endl
                << "--------------------------------------------------------" << endl;
            string food1, food2, food3, food4, checkout;
            ifstream inputfile("Menu.txt");
            if (!inputfile) {
                cerr << "Error: could not open Menu.txt." << endl;
                return 1;
            }

            double food1Small, food1Medium, food1Large;
            double food2Small, food2Medium, food2Large;
            double food3Small, food3Medium, food3Large;
            double food4Small, food4Medium, food4Large;

            getline(inputfile, food1);
            inputfile >> food1Small >> food1Medium >> food1Large;
            inputfile.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(inputfile, food2);
            inputfile >> food2Small >> food2Medium >> food2Large;
            inputfile.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(inputfile, food3);
            inputfile >> food3Small >> food3Medium >> food3Large;
            inputfile.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(inputfile, food4);
            inputfile >> food4Small >> food4Medium >> food4Large;
            getline(inputfile, checkout);
            inputfile >> checkout;

            if (!inputfile) {
                cerr << "Error: Menu.txt does not contain four item names and three prices per item." << endl;
                return 1;
            }

            cout << "A. " << food1 << setw(11) << "$" << food1Small << setw(14) << "$" << food1Medium << setw(16) << "$" << food1Large << endl;
            cout << "B. " << food2 << setw(8) << "$" << food2Small << setw(14) << "$" << food2Medium << setw(16) << "$" << food2Large << endl;
            cout << "C. " << food3 << setw(8) << "$" << food3Small << setw(14) << "$" << food3Medium << setw(16) << "$" << food3Large << endl;
            cout << "D. " << food4 << setw(18) << "$" << food4Small << setw(14) << "$" << food4Medium << setw(16) << "$" << food4Large << endl;
			cout << "E." << checkout << endl;

                //<< "A. Cheese pizza" << setw(11) << "$2.50" << setw(14) << "$4.50" << setw(16) << "$6.00" << endl
                //<< "B. Pepperoni pizza" << setw(8) << "$3.00" << setw(14) << "$5.00" << setw(16) << "$6.50" << endl
                //<< "C. Turkey Sandwich" << setw(8) << "$2.00" << setw(14) << "$3.50" << setw(16) << "$4.50" << endl
                //<< "D. Salad" << setw(18) << "$1.50" << setw(14) << "$2.50" << setw(16) << "$3.00" << endl
                //<< "E. Checkout" << endl;

            char choice;
            cout << "Enter choice (A-E): ";
            cin >> choice;
            choice = toupper(choice);

            // validate choice
            while (choice < 'A' || choice > 'E') {
                cout << "Invalid selection. Please enter A, B, C, D, or E: ";
                cin >> choice;
                choice = toupper(choice);
            }

            if (choice == 'E') {
                // proceed to checkout
                break;
            }

            cout << "Please select a size for your item (s/m/l): ";
            char itemCode;
            cin >> itemCode;
            char size = tolower(itemCode);
            while (size != 's' && size != 'm' && size != 'l') {
                cout << "Invalid size. Please enter s, m, or l: ";
                cin >> itemCode;
                size = tolower(itemCode);
            }

            // Determine item, price, and inventory position from the selection
            string FoodName;
            double price = 0.0;
            size_t inventoryIndex = 0;
            char ch = toupper(choice);
            switch (ch) {
            case 'A':
                FoodName = food1;
                inventoryIndex = 0;
                switch (size) {
                case 's': price = food1Small; break;
                case 'm': price = food1Medium; break;
                case 'l': price = food1Large; break;
                default: price = 0.0; break;
                }
                break;
            case 'B':
                FoodName = food2;
                inventoryIndex = 1;
                switch (size) {
                case 's': price = food2Small; break;
                case 'm': price = food2Medium; break;
                case 'l': price = food2Large; break;
                default: price = 0.0; break;
                }
                break;
            case 'C':
                FoodName = food3;
                inventoryIndex = 2;
                switch (size) {
                case 's': price = food3Small; break;
                case 'm': price = food3Medium; break;
                case 'l': price = food3Large; break;
                default: price = 0.0; break;
                }
                break;
            case 'D':
                FoodName = food4;
                inventoryIndex = 3;
                switch (size) {
                case 's': price = food4Small; break;
                case 'm': price = food4Medium; break;
                case 'l': price = food4Large; break;
                default: price = 0.0; break;
                }
                break;
            }

            if (remainingInventory[inventoryIndex] == 0) {
                cout << FoodName << " is out of stock.\n";
                continue;
            }

            cout << "Enter Quantity: ";
            int quantity = 0;
            while (!(cin >> quantity) || quantity < 1 || quantity > remainingInventory[inventoryIndex]) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Enter a quantity from 1 to " << remainingInventory[inventoryIndex] << ": ";
            }
            remainingInventory[inventoryIndex] -= quantity;

            // add to cart
            cartNames.push_back(FoodName);
            cartQuantities.push_back(quantity);
            cartUnitPrices.push_back(price);

            subtotal += quantity * price;

            // Append formatted line to receipt accumulator
            receiptAccumulator << left << setw(30) << FoodName
                << right << setw(8) << quantity
                << right << setw(12) << fixed << setprecision(2) << price
                << right << setw(12) << fixed << setprecision(2) << (quantity * price)
                << "\n";

            cout << "Added " << quantity << " x " << FoodName << " at $" << price << " each to cart.\n";

            // clear leftover newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // After shopping loop, ask member and cashier notes
        cout << "Member Y/N: ";
        char member;
        cin >> member;

        // Cashier notes
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string cashiernotes;
        cout << "Enter cashier notes: ";
        getline(cin, cashiernotes);

        // calculations
        double discount = (member == 'Y' || member == 'y') ? subtotal * 0.10 : 0.0;
        double taxable_base = subtotal - discount;

        const double arkansasRate = 0.065;   // 6.5%
        const double faulknerRate = 0.005;   // 0.5%
        const double conwayRate = 0.02125;   // 2.125%

        double arkansasTax = taxable_base * arkansasRate;
        double faulknerTax = taxable_base * faulknerRate;
        double conwayTax = taxable_base * conwayRate;
        double totalTax = arkansasTax + faulknerTax + conwayTax;

        double totalBeforeTip = taxable_base + totalTax;

        // Tip suggestions
        double tipA = totalBeforeTip * 0.15; // 15%
        double tipB = totalBeforeTip * 0.20; // 20%
        double tipC = totalBeforeTip * 0.25; // 25%
        double tipAmount = 0.0;

        // print receipt header and accumulated item lines
		ofstream receiptFile("receipt.txt");

        cout << "\n----Receipt----\n";
        receiptFile << "\n----Receipt----\n";
        cout << "Customer: " << customerName << "\n\n";
		receiptFile << "Customer: " << customerName << "\n\n";
        cout << left << setw(30) << "Item" << right << setw(8) << "Qty" << right << setw(12) << "Unit" << right << setw(12) << "Line Total" << "\n";
		receiptFile << left << setw(30) << "Item" << right << setw(8) << "Qty" << right << setw(12) << "Unit" << right << setw(12) << "Line Total" << "\n";
        cout << receiptAccumulator.str();

        cout << left << "\nSubtotal:       $" << subtotal << "\n";
		receiptFile << left << "\nSubtotal:       $" << subtotal << "\n";
        cout << left << "Discount:       $" << discount << "\n";
		receiptFile << left << "Discount:       $" << discount << "\n";
        cout << left << "Taxable Amount: $" << taxable_base << "\n";
		receiptFile << left << "Taxable Amount: $" << taxable_base << "\n";

        cout << "\nTaxes:\n";
		receiptFile << "\nTaxes:\n";
        cout << left << setw(30) << "Tax Name" << right << setw(8) << "Rate" << right << setw(14) << "Amount" << "\n";
		receiptFile << left << setw(30) << "Tax Name" << right << setw(8) << "Rate" << right << setw(14) << "Amount" << "\n";
        cout << left << setw(30) << "Arkansas State Tax" << right << setw(8) << "6.5%" << right << setw(13) << "$" << arkansasTax << "\n";
		receiptFile << left << setw(30) << "Arkansas State Tax" << right << setw(8) << "6.5%" << right << setw(13) << "$" << arkansasTax << "\n";
        cout << left << setw(30) << "Faulkner County Tax" << right << setw(8) << "0.5%" << right << setw(13) << "$" << faulknerTax << "\n";
		receiptFile << left << setw(30) << "Faulkner County Tax" << right << setw(8) << "0.5%" << right << setw(13) << "$" << faulknerTax << "\n";
        cout << left << setw(30) << "Conway Municipal Tax" << right << setw(8) << "2.125%" << right << setw(13) << "$" << conwayTax << "\n";
		receiptFile << left << setw(30) << "Conway Municipal Tax" << right << setw(8) << "2.125%" << right << setw(13) << "$" << conwayTax << "\n";
        cout << left << setw(30) << "Total Tax" << right << setw(8) << "" << right<< setw(13) << "$" << totalTax<< "\n";
        receiptFile << left << setw(30) << "Total Tax" << right << setw(8) << "" << right << setw(13) << "$" << totalTax << "\n";

        cout<< left<< "\nTotal (Subtotal - Discount + Tax): $"<< totalBeforeTip<< "\n";
		receiptFile << left << "\nTotal (Subtotal - Discount + Tax): $" << totalBeforeTip << "\n";
        receiptFile.close();
        // tip menu
        cout << "\nTip Selection\t\t Amount\n";
        cout << "A. 15%\t\t$" << tipA << "\n";
        cout << "B. 20%\t\t$" << tipB << "\n";
        cout << "C. 25%\t\t$" << tipC << "\n";
        cout << "D. Other Amount\n";

        cout << "\nWhat tip do you choose? ";
        char tipChoice;
        cin >> tipChoice;
        tipChoice = toupper(tipChoice);
        while (tipChoice < 'A' || tipChoice > 'D') {
            cout << "Invalid selection. Enter A, B, C, or D: ";
            cin >> tipChoice;
            tipChoice = toupper(tipChoice);
        }

        if (tipChoice == 'A') tipAmount = tipA;
        else if (tipChoice == 'B') tipAmount = tipB;
        else if (tipChoice == 'C') tipAmount = tipC;
        else {
            cout << "How much would you like to tip? ";
            cin >> tipAmount;
            while (tipAmount < 0.0) {
                cout << "Tip cannot be negative. Enter amount: ";
                cin >> tipAmount;
            }
        }

        double finalTotal = totalBeforeTip + tipAmount;

        cout << left << "\nTip:            $" << tipAmount << "\n";
        cout << left << "Final Total:    $" << finalTotal << "\n";

        cout << left << "Cashier Notes: " << cashiernotes << "\n";

        // Loyalty points: one point per $3 spent (rounded down)
        int loyaltyPoints = static_cast<int>(finalTotal / 3.0);
        cout << "Loyalty Points: ";
        for (int i = 0; i < loyaltyPoints; ++i) cout << '*';
        cout << " (" << loyaltyPoints << ")\n";

        // Inventory / summary table
        cout << "\n----Inventory Table----\n";
        cout << left << setw(30) << "Item" << right << setw(8) << "Qty" << right << setw(12) << "Unit Price" << "\n";
        for (size_t i = 0; i < cartNames.size(); ++i) {
            cout << left << setw(30) << cartNames[i]
                << right << setw(8) << cartQuantities[i]
                << right << setw(12) << cartUnitPrices[i] << "\n";
        }

        // update daily totals
        ++totalCustomers;
        grandTotalSales += finalTotal;

        // ask if another customer
        cout << "\nProcess another customer? (Y/N): ";
        char more;
        cin >> more;
        more = toupper(more);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (more != 'Y') break;
    }

	// End-of-day summary
	cout << "\n---End of Day Summary---\n";
	cout << "Total Customers: " << totalCustomers << "\n";
	cout << "Grand Total Sales: $" << grandTotalSales << "\n";

	cout << "\n---Daily Inventory Summary---\n";
	cout << left << setw(24) << "Item"
		<< right << setw(12) << "Original"
		<< right << setw(12) << "Change"
		<< right << setw(12) << "New Amount" << "\n";
	for (size_t i = 0; i < inventoryNames.size(); ++i) {
		int change = remainingInventory[i] - startingInventory[i];
		cout << left << setw(24) << inventoryNames[i]
			<< right << setw(12) << startingInventory[i]
			<< right << setw(12) << change
			<< right << setw(12) << remainingInventory[i] << "\n";
	}

	return 0;
}
