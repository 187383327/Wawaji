#pragma once
#include "serial_win32.h"

namespace nim_wwj
{
	enum wwj_cmd
	{
		frame_cmd_game_start = 0x00,//��Ϸ��ʼ
		frame_cmd_control = 0x01, //����ָ��
		frame_cmd_strong_claw_power = 0x0A, //ǿץ������
		frame_cmd_weak_claw_power = 0x0B, //��ץ������
		frame_cmd_game_time = 0x0C,//��Ϸʱ��
		frame_cmd_check_device = 0x0E,//����豸
		frame_cmd_heartbeat = 0x02,//��������
		frame_cmd_game_end = 0x80,//��Ϸ����
	};
	
	enum game_type
	{
		kstrong = 0,//ǿ����
		kweak    //������
	};

	class WwjControl_Wmq :public WwjControl
	{
	public:
		WwjControl_Wmq();
		~WwjControl_Wmq();
		virtual void CloseSerial();
		virtual bool CrownBlockReset();//�쳵��λ
		virtual bool SerialDirectectOpt(serial_direction_opt_type_e type);//���޻��������
		virtual void SerialSetStepSize(unsigned char step_size);//���޻�����
		virtual void  Pay(int coins);//���Ϸ֣��Ϸ�֮ǰӦ�ȵ���CheckNormal�ӿڼ���豸״̬ ����ɻص�����
		virtual bool QueryDeviceInfo();//��ѯ�ն���Ŀ�����ڲ�ѯ�豸����Ŀ״��������״̬�� ����ɻص�����
		virtual bool CheckNormal();//��ѯ����, �û���ѯ�Ƿ�����,����ɻص�����
		wwj_set_param_t GetSettingParam();//��ȡ���޻�����
		virtual bool  SetSettingParam(wwj_set_param_t param);//�������޻��豸����
		virtual void StartSerialReadThread();
	private:
		unsigned char send_data_[BUF_LEN];
	private:
		wwj_set_param_t wwj_set_param_;
		int wwj_step_size_;
		int opt_count_;
	};
}
