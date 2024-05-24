#include <iostream>
#include <random>
#include "MatchTable.h"

std::random_device g_rnd;     // 非決定的な乱数生成器でシード生成機を生成
std::mt19937 g_mt(g_rnd()); //  メルセンヌツイスターの32ビット版、引数は初期シード

using namespace std;

void MatchTable::set_cpr(int n_courts, int n_players, int n_rounds, bool dr) {
	m_n_courts = n_courts;
	m_n_players = n_players;
	m_n_rounds = n_rounds;
	m_desc_rest = dr;
	m_n_can_play = n_courts * 4;
	m_n_rest = n_players - m_n_can_play;
	m_restix = m_n_can_play;
	m_is_rest.resize(n_players);
	//
	gen_random();
}
void MatchTable::print() const {
	for(int r = 0; r != m_match.size(); ++r) {
		for(int i = 0; i != m_n_players; ++i) {
			if( i%4 == 0 && i < m_n_can_play )
				cout << "[";
			cout << m_match[r][i];
			if( i < m_n_can_play ) {
				switch(i%4) {
				case 0: cout << ",";	break;
				case 1: cout << "-";	break;
				case 2: cout << ",";	break;
				case 3: cout << "] ";	break;
				}
			} else
				cout << " ";
		}
		cout << "\n";
	}
}
//	ix, ix+1 ペアを作る
bool MatchTable::build_pairs(const vector<int>& ar, int ix) {
	if( ix >= m_n_can_play ) return true;
	return false;
}
void MatchTable::gen_round_random() {
	vector<int> ar(m_n_players);
	for(int p = 0; p != m_n_players; ++p) ar[p] = p;
	if( m_n_rest == 0 ) {
		shuffle(ar.begin(), ar.end(), g_mt);
	} else {
		ar.resize(m_n_can_play);
		if( m_desc_rest ) {			//	休憩：降順
			if( (m_restix -= m_n_rest) < 0 )
				m_restix += m_n_players;
		} else {					//	休憩：昇順
			if( (m_restix += m_n_rest) >= m_n_players )
				m_restix -= m_n_players;
		}
		fill(m_is_rest.begin(), m_is_rest.end(), false);
		for(int p = 0; p != m_n_rest; ++p)
			m_is_rest[(m_restix+p) % m_n_players] = true;	//	休憩中フラグON
		int ix = 0;
		for(int p = 0; p != m_n_players; ++p) {
			if( !m_is_rest[p] )		//	非休憩中の場合
				ar[ix++] = p;
		}
		shuffle(ar.begin(), ar.end(), g_mt);
		for(int i = 0; i != m_n_rest; ++i)
			ar.push_back((m_restix+i)%m_n_players);
	}
	//	組んでいないペアを作る
	vector<bool> is_assigned_rest(m_is_rest);
	m_plst.resize(m_n_can_play);
	build_pairs(ar, 0);
}
void MatchTable::gen_random() {
	m_match.clear();
	//	１ラウンド目は 1から昇順に対戦リストに加えていく
	vector<int> t(m_n_players);
	for(int p = 0; p != m_n_players; ++p) t[p] = p;
	m_match.push_back(t);
	for(int i = 1; i < m_n_rounds; ++i)
		gen_round_random();
}
