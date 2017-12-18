#ifndef SERIAL_WIN32_H
#define SERIAL_WIN32_H
#include <windows.h>

namespace nim_wwj
{
#define kSerialOptSuccess 200
#define kSerialOptFailed 100
#define BUF_LEN 240
	//���޻����ò���
	typedef struct wwj_set_param_s
	{
		unsigned char once_need_coin;//����һ��
		unsigned char game_paly_levle;//�н�����(1-99)  (�����N��ǿץ����������������Ϸ�Ѷ�)
		unsigned char auto_down_claw;//�Զ���ץʱ��(5-60)
		unsigned char power_time;//ǿ��ʱ��(1-60)
		unsigned char weak_time;//����ʱ�䣨1-60)
		unsigned char prize_pattern;//�н�ģʽ(0 / 1 / 2  ������̶���ȡ��)
		unsigned char sell_pattern;//����ģʽ(0/1/2  ǿ����ǿ�ͣ�ǿͶ)
		unsigned char prize_score;   //����Ͷ���ͷ�(0 - 20, 0Ϊ�ر�)
		unsigned char prize_claw_power;//�н�ץ��(5-50)      (����ܰ汾��Ч)
		unsigned char power_claw;//	ǿצץ��(5-50)        (��צ��ͣǿ����)
		unsigned char top_claw_power;//����ץ��(0 - 40, ����������צץ����ͬ)   (��ͣͣ��ץ��)
		unsigned char weak_claw_power;// 	��צץ��(2 - 40)      (�쳵�ع�����)
		unsigned char weak_strong;//������ǿ   (0-2)= 1��     0����ģʽ��1��ǿģʽ��2ħ��ģʽ
		unsigned char sell_function;//	�������ܿ���(0 / 1)
		unsigned char sell_count;//��������  (1 -100)= 10��
		unsigned char prize_inductor;//     �н���Ӧ������(0 / 1)
		unsigned char air_claw_thing; //    ����ץ�﹦�ܿ���(0 / 1)
		unsigned char start_score_remain;//  	����������������(0 / 1)
		unsigned char shake_clean_score_funtion;// 	ҡ����ֹ��ܿ���(0 / 1)
		unsigned char front_back_speed;//     ǰ���ٶ�(5 - 50, Ĭ��50)
		unsigned char left_right_speed;//     �����ٶ�(5 - 50, Ĭ��50)
		unsigned char up_down_speed;//     �����ٶ�(5 - 50, Ĭ��50)
	}wwj_set_param_t;

	typedef struct serial_param_s
	{
		int bound_rate; //������
		int byte_size; //����λ
		int parity;   //��żУ�顣Ĭ��Ϊ��У�顣NOPARITY 0�� ODDPARITY 1��EVENPARITY 2��MARKPARITY 3��SPACEPARITY 4
		int stop_bits;//ֹͣλ
		int fbinary;//������ģʽ
		int fparity;//��żУ��
	}serial_param_t;

	typedef enum
	{
		kfront = 0, /*ǰ*/
		kback, /*��*/
		kleft, /*��*/
		kright,/*��*/
		kclaw /*��ץ*/
	}serial_direction_opt_type_e;

	typedef enum
	{

		kgamepay = 0,//���Ϸ�
		kgameend,//��Ϸ����
		kgameprize,//�н�
		kgameonline,//��ѯ����
		kgamecheckaccount,//��ѯ�ն���Ŀ
	}wwj_callback_func_type_e;

	typedef enum
	{
		error = -1,
		normal = 0, //����
		left_error, //�������
		right_error,//���ҹ���
		front_error,//��ǰ����
		back_error,//������
		down_error,//���¹���
		up_error,//���Ϲ���
		shake_error,//ҡ�ι���
		light_eye_error,//���۹���
	}wwj_device_status_e;

	//���޻���������
	enum wwj_mainboard_index
	{
		kMainboard01 = 0x7E,
	};

	//�ص�����
	typedef void(*wwj_callback_func)(wwj_callback_func_type_e type, int code, wwj_device_status_e status);

	class WwjControl
	{
	public:
		WwjControl();
		virtual ~WwjControl();
		virtual bool OpenSerial(const char* com);//�򿪴���
		virtual void CloseSerial();//�رմ���
		virtual bool SetSerialParam(serial_param_t param);//���ô��ڲ���
		virtual bool CrownBlockReset();//�쳵��λ
		wwj_set_param_t GetSettingParam();//��ȡ���޻�����
		bool  SetSettingParam(wwj_set_param_t param);//�������޻��豸����
		virtual bool SerialDirectectOpt(serial_direction_opt_type_e type);//���޻��������
		virtual void SerialSetStepSize(unsigned char step_size);//���޻�����
		virtual void  Pay(int coins);//���Ϸ֣��Ϸ�֮ǰӦ�ȵ���CheckNormal�ӿڼ���豸״̬ ����ɻص�����
		virtual bool QueryDeviceInfo();//��ѯ�ն���Ŀ�����ڲ�ѯ�豸����Ŀ״��������״̬�� ����ɻص�����
		virtual bool CheckNormal();//��ѯ����, �û���ѯ�Ƿ�����,����ɻص�����
		virtual void SetOptFuncCb(wwj_callback_func cb) { wwj_opt_cb_ = cb; }//���ûص�����
		virtual wwj_callback_func GetOptFuncCb() { return wwj_opt_cb_; }//��ȡ�ص�����
		HANDLE GetSerialHandle() { return serial_handle_; } //��ȡ���ھ��
		void SetMainBoardIndex(wwj_mainboard_index index) { wwj_mainboard_index_ = index; }//������������
		virtual void StartSerialReadThread();
		
	private:
		unsigned char cmd_data_[BUF_LEN];
		unsigned char send_data_[BUF_LEN];
		wwj_callback_func wwj_opt_cb_;
		wwj_set_param_t wwj_setting_param_;
		unsigned char wwj_step_size_;
		wwj_mainboard_index wwj_mainboard_index_;
	private:
		int SerialCmdHelp(unsigned char* buf, unsigned int buf_size, unsigned char cmd, unsigned char* data, size_t data_size, int* length);
		int SetSerialComTimeout();

	public:
		HANDLE serial_handle_;
		HANDLE serial_read_thread_id_;//���ڶ��߳�

	};
}
#endif
