#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <string>

using namespace std;

// -------------------
// Is Zamanlama (Job Sequencing with Deadlines)
// -------------------
struct Job {
    char id;
    int deadline;
    int profit;
};

void isZamanlama(vector<Job> jobs) {
    // En yuksek kardan basla
    sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });

    int maxD = 0;
    for (auto& j : jobs) maxD = max(maxD, j.deadline);

    vector<char> slot(maxD + 1, '-');
    int toplamKar = 0;

    for (auto& j : jobs) {
        for (int t = min(maxD, j.deadline); t >= 1; t--) {
            if (slot[t] == '-') {
                slot[t] = j.id;
                toplamKar += j.profit;
                break;
            }
        }
    }

    cout << "Slotlar: ";
    for (int t = 1; t <= maxD; t++) cout << slot[t] << " ";
    cout << "\nToplam kar: " << toplamKar << "\n";
}

// -------------------
// Aktivite Zamanlama
// -------------------
struct Activity {
    int id;
    int start;
    int finish;
};

void aktiviteZamanlama(vector<Activity> acts) {
    sort(acts.begin(), acts.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    cout << "Secilen aktiviteler: ";
    int lastFinish = -1;
    for (auto& a : acts) {
        if (a.start >= lastFinish) {
            cout << "a" << a.id << " ";
            lastFinish = a.finish;
        }
    }
    cout << "\n";
}

// -------------------
// Huffman (encode/decode)
// -------------------
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

struct Cmp {
    bool operator()(Node* a, Node* b) { return a->freq > b->freq; }
};

void buildCodes(Node* root, string path, string codes[256]) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[(unsigned char)root->ch] = path.empty() ? "0" : path;
        return;
    }
    buildCodes(root->left, path + "0", codes);
    buildCodes(root->right, path + "1", codes);
}

string encodeText(const string& text, string codes[256]) {
    string bits;
    for (char c : text) bits += codes[(unsigned char)c];
    return bits;
}

string decodeBits(Node* root, const string& bits) {
    string out;
    Node* cur = root;
    for (char b : bits) {
        cur = (b == '0') ? cur->left : cur->right;
        if (cur && !cur->left && !cur->right) {
            out.push_back(cur->ch);
            cur = root;
        }
    }
    return out;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void huffmanDemo(const string& text) {
    int freq[256] = {0};
    for (char c : text) freq[(unsigned char)c]++;

    priority_queue<Node*, vector<Node*>, Cmp> pq;
    for (int i = 0; i < 256; i++)
        if (freq[i] > 0) pq.push(new Node((char)i, freq[i]));

    if (pq.empty()) {
        cout << "Metin bos.\n";
        return;
    }

    while ((int)pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(new Node(a, b));
    }

    Node* root = pq.top();

    string codes[256];
    buildCodes(root, "", codes);

    cout << "Kodlar:\n";
    for (int i = 0; i < 256; i++) {
        if (!codes[i].empty()) cout << "  '" << (char)i << "' : " << codes[i] << "\n";
    }

    string bits = encodeText(text, codes);
    cout << "Encode bits: " << bits << "\n";

    string decoded = decodeBits(root, bits);
    cout << "Decode metin: " << decoded << "\n";

    freeTree(root);
}

int main() {
    cout << "GREEDY ALGORITMALAR\n";
    cout << "-------------------\n";

    // 1) Is Zamanlama (deadline+profit)
    vector<Job> jobs = {
        {'a',2,100},
        {'b',1,19},
        {'c',2,27},
        {'d',1,25},
        {'e',3,15}
    };

    auto t1 = chrono::high_resolution_clock::now();
    cout << "[Is Zamanlama]\n";
    isZamanlama(jobs);
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Sure: " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " us\n\n";

    // 2) Aktivite Zamanlama
    vector<Activity> acts = {
        {1,1,4},{2,3,5},{3,0,6},{4,5,7},{5,3,8},
        {6,5,9},{7,6,10},{8,8,11},{9,8,12},{10,2,13},{11,12,14}
    };

    t1 = chrono::high_resolution_clock::now();
    cout << "[Aktivite Zamanlama]\n";
    aktiviteZamanlama(acts);
    t2 = chrono::high_resolution_clock::now();
    cout << "Sure: " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " us\n\n";

    // 3) Huffman
    cout << "[Huffman Encode/Decode]\n";
    string text = "ABBCCCDDDDEEEEEFF";
    cout << "Metin: " << text << "\n";

    t1 = chrono::high_resolution_clock::now();
    huffmanDemo(text);
    t2 = chrono::high_resolution_clock::now();
    cout << "Sure: " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " us\n";

    return 0;
}
