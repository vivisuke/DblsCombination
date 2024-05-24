#pragma once

#include <vector>

class MatchTable
{
public:
	MatchTable(int n_courts, int n_players, int n_rounds, bool desc = true) {
		set_cpr(n_courts, n_players, n_rounds, desc);
	}
public:
	void	print() const;
public:
	void	set_cpr(int n_courts, int n_players, int n_rounds, bool dr = true);
	void	gen_random();
	void	gen_round_random();
	bool	build_pairs(const vector<int>& ar, int ix);
private:
	int		m_n_courts;		//	コート数
	int		m_n_players;	//	プレイヤー数
	int		m_n_rounds;		//	ラウンド数
	bool	m_desc_rest;	//	休憩順、true for 降順
	int		m_n_can_play;	//	非休憩人数
	int		m_n_rest;		//	休憩人数
	int		m_restix;

	std::vector<std::vector<int>>	m_match;		//	ラウンドごとの各プレイヤー番号リスト
	std::vector<bool>	m_is_rest;					//	休憩中？
	std::vector<int>	m_plst;						//	ペアリスト
};

