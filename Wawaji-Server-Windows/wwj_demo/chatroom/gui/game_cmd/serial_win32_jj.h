/*�޾�����*/
#pragma once
#include "serial_win32.h"
namespace nim_wwj
{
	struct RoomInfo
	{
		int id_;
		int price_;
		int game_time_;
		int auto_start_;
		string status_;
	};

	class WwjControl_jj :public WwjControl,public virtual nbase::SupportWeakCallback
	{
	public:
		WwjControl_jj();
		~WwjControl_jj();
		virtual bool SetSerialParam(serial_param_t param);
		virtual bool OpenSerial(const char* com);
		virtual void CloseSerial();
		virtual bool CrownBlockReset();//�쳵��λ
		virtual bool SerialDirectectOpt(serial_direction_opt_type_e type);//���޻��������
		virtual void SerialSetStepSize(unsigned char step_size);//���޻�����
		virtual void  Pay(int coins);//���Ϸ֣��Ϸ�֮ǰӦ�ȵ���CheckNormal�ӿڼ���豸״̬ ����ɻص�����
		virtual bool QueryDeviceInfo();//��ѯ�ն���Ŀ�����ڲ�ѯ�豸����Ŀ״��������״̬�� ����ɻص�����
		virtual bool CheckNormal();//��ѯ����, �û���ѯ�Ƿ�����,����ɻص�����
		wwj_set_param_t GetSettingParam();//��ȡ���޻�����
		bool  SetSettingParam(wwj_set_param_t param);//�������޻��豸����
		virtual void StartSerialReadThread();
		virtual void SetOptFuncCb(wwj_callback_func cb) { wwj_opt_cb_ = cb; }
	private:
		unsigned char send_data_[BUF_LEN];
	private:
		wwj_set_param_t wwj_set_param_;
		int wwj_step_size_;
		int opt_count_;
		string identifying_;
		wwj_callback_func wwj_opt_cb_;
		string wss_url_;
		std::list<RoomInfo> room_info_;
	};
}