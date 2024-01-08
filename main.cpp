#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;

using namespace std;

ull p = 31ull, mod = 1, inf = (ull) 1e5;
vector <ull> p_pow(inf);


vector <ull> z_function(const string &s) {
	ull n = s.size();
	vector <ull> z(n);
	for (ull i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i,  r = i + z[i] - 1;
	}
	return z;
}

void get_pow(void) {
    p_pow[0] = 1;
    for (ull i = 1; i < p_pow.size(); ++i)
        p_pow[i] = (p_pow[i - 1] * p) % mod;
}

vector <ull> get_hash_for_a(const string &a) {
    vector <ull> h(a.size());
    for (ull i = 0; i < a.size(); ++i) {
        h[i] = ((a[i] - 'a' + 1) * p_pow[i]) % mod;
        if (i) h[i] += h[i - 1];
    }
    return h;
}

ull get_hash_for_b(const string &b) {
    ull h = 0;
    for (ull i = 0; i < b.size(); ++i)
        h += ((b[i] - 'a' + 1) * p_pow[i]) % mod;
    return h;
}

ull hash_solve(const vector <ull> &hash_a, const ull &hash_b, const string &b, const string &a) {
    ull ans = 0;
    for (ll i = 0; i + b.size() - 1 < a.size(); ++i) {
        ll temp_h = hash_a[i + b.size() - 1];
        if (i) temp_h -= hash_a[i - 1];
        if (temp_h == hash_b * p_pow[i])
            ans++;
    }
    return ans;
}

ull z_function_solve(const string &s, ull n, const string &b, const vector <ull> &z) {
    ull m = b.size(), ans = 0;
    for (ll i = 0; i < n; ++i)
        if (z[i + m + 1] == m)
            ++ans;
    return ans;
}

signed main() {
    ifstream in1, in2;
    ofstream out1, out2;
    in1.open("input_for_string.txt");
    in2.open("input_for_substr.txt");
    out1.open("output_for_hash_function.txt");
    out2.open("output_for_z_function.txt");
    string s;
    vector <string> a, b;
    mod <<= 63;
    get_pow();
    while (in1 >> s)
        a.push_back(s);
    while (in2 >> s)
        b.push_back(s);
    in1.close(), in2.close();
    for (ll i = 0; i < a.size(); ++i) {
        string s = b[i] + '#' + a[i];
        vector <ull> hash_a = get_hash_for_a(a[i]), z = z_function(s);
        ull hash_b = get_hash_for_b(b[i]);
        ull ans_hash = hash_solve(hash_a, hash_b, b[i], a[i]);
        ull ans_z_function = z_function_solve(s, a[i].size(), b[i], z);
        out1 << ans_hash << endl;
        out2 << ans_z_function << endl;
    }
    out1.close(), out2.close();
    return 0;
}
