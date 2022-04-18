#include <bits/stdc++.h>

using namespace std;

struct page
{
    int page_no; // If page number = -1 means there was no page
    map<int, int> record;
    int pre_page_address;
    int next_page_address;
    int free_space_address;
    int count;
    page *prec;
    page *next;
};

page *root = nullptr;
int total_page = 0;

page *init_page()
{
    page *new_page = new page();
    new_page->page_no = total_page;
    new_page->pre_page_address = total_page - 1;
    total_page++;
    new_page->next_page_address = -1;
    new_page->free_space_address = 0;
    new_page->count = 0;
    new_page->prec = nullptr;
    new_page->next = nullptr;
    return new_page;
}

void insert(int Page_size, int record_size, int primary_key)
{

    if (Page_size - 16 < record_size + 4)
    {
        cout << "Record cannot store in file" << endl;
        return;
    }
    if (root == nullptr)
    {
        // Means there is no page so created first page
        root = init_page();
        root->record.insert(make_pair(primary_key, record_size));
        root->count++;
        root->free_space_address = record_size;
        return;
    }
    page *curr = root;
    while (curr != nullptr)
    {
        if ((curr->free_space_address) + 16 + (curr->count) * 4 + (record_size + 4) <= Page_size)
        {
            // Store the data in existing page
            curr->record.insert(make_pair(primary_key, record_size));
            curr->count++;
            curr->free_space_address += record_size;

            return;
        }
        else
        {
            if (curr->next == nullptr)
            {
                // It is last page so add new page
                page *new_page = init_page();
                curr->next_page_address = new_page->page_no;
                curr->next = new_page;
                new_page->prec = curr;
                new_page->record.insert(make_pair(primary_key, record_size));
                new_page->count++;
                new_page->free_space_address += record_size;
                return;
            }
            else
            {
                // Goes to next page
                curr = curr->next;
            }
        }
    }
}

void display()
{
    if (root == nullptr)
    {
        cout << 0 << endl;
        return;
    }
    page *curr = root;
    cout << total_page<<" ";
    while (curr != nullptr)
    {
        cout <<curr->count<<" ";
        curr = curr->next;
    }
    cout<<endl;
}

// void search(int primary_key)
// {
//     int page_no = -1;
//     int slot_no = -1;
//     int count;
//     page *curr = root;
//     while (curr != nullptr)
//     {
//         count = 0;
//         for(auto x : curr->record)
//         {
//             if(x.first == primary_key)
//             {
//                 page_no = curr->page_no;
//                 slot_no = count;
//             }
//             count++;
//         }
//         curr = curr->next;
//     }
//     cout<<"Page no. : "<<page_no<<" Slot no. : "<<slot_no<<endl;
// }

void search(int primary_key)
{
    int slot_no;
    page *curr = root;
    while (curr != nullptr)
    {
        slot_no = 0;
        for (auto x : curr->record)
        {
            if (x.first == primary_key)
            {
                cout << curr->page_no<< " "<<slot_no << endl;
                return;
            }
            slot_no++;
        }
        curr = curr->next;
    }
    cout <<  -1 << " " << -1 << endl;//Not found
    return;
}

int main()
{
    
    #ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    #endif
    int size;
    cin >> size;
    int choice;
    int r_size, p_key;
    while (1)
    {
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> r_size >> p_key;
            // call function for insert
            insert(size, r_size, p_key);
            break;
        case 2:
            // call function for display status
            display();
            break;
        case 3:
            cin >> p_key;
            // call function for search
            search(p_key);
            break;
        case 4:
            // call quit function
            exit(0);
            break;
        }
    }
}