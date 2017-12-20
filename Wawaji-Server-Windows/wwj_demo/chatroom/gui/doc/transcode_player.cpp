#include "transcode_player.h"
using namespace ui;

namespace nim_chatroom
{

void TranscodeAnimationPlayer::Init()
{
	__super::Init();
	is_trans_compelete_ = false;
}

int TranscodeAnimationPlayer::GetCurrentValue()
{
	int detaValue = 0;
	if (is_trans_compelete_)
	{
		detaValue = int(abs(m_endValue - m_startValue) * (m_palyedMillSeconds / m_totalMillSeconds));
	}
	else
	{
		const double kBaseNumber = 0.97716;
		// �㷨����Ϊ1-0.97716��n�η�(nΪ����������)
		detaValue = int(abs(m_endValue - m_startValue) * (1 - pow(kBaseNumber, m_palyedMillSeconds / 1000)));
	}

	int currentValue = 0;
	if (m_endValue > m_startValue) {
		currentValue = m_startValue + detaValue;
	}
	else {
		currentValue = m_startValue - detaValue;
	}

	return currentValue;
}

}