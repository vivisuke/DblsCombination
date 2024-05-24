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
	int		m_n_courts;		//	�R�[�g��
	int		m_n_players;	//	�v���C���[��
	int		m_n_rounds;		//	���E���h��
	bool	m_desc_rest;	//	�x�e���Atrue for �~��
	int		m_n_can_play;	//	��x�e�l��
	int		m_n_rest;		//	�x�e�l��
	int		m_restix;

	std::vector<std::vector<int>>	m_match;		//	���E���h���Ƃ̊e�v���C���[�ԍ����X�g
	std::vector<bool>	m_is_rest;					//	�x�e���H
	std::vector<int>	m_plst;						//	�y�A���X�g
};

