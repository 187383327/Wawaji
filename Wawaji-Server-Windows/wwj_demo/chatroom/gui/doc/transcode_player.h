#pragma once

namespace nim_chatroom
{

/** @class TranscodeAnimationPlayer
  * @brief �ĵ��б���ת��������Ķ���������
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/12/19
  */
class TranscodeAnimationPlayer : public ui::AnimationPlayerBase
{
public:
	static const int kEndValue = 10000; // ���ֵ����Ϊ10000���������100���ȡ����С����İٷֱ�

	virtual void Init() override;
	virtual int GetCurrentValue() override;

	/**
	* �Ƿ��Ѿ�ת�����(ת����ɺ�ʣ��Ľ��Ȼ�1��������ִ����)
	* @return bool true ��ɣ�false δ���
	*/
	bool IsTranscodeCompelete() { return is_trans_compelete_; }

	/**
	* �����Ѿ�ת�����
	* @return void	�޷���ֵ
	*/
	void SetTranscodeCompelete() { is_trans_compelete_ = true; }

private:
	bool is_trans_compelete_ = false;
};

}