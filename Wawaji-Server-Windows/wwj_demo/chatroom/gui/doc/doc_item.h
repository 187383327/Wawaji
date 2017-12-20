#pragma once
#include "transcode_player.h"

namespace nim_chatroom
{

/** @class DocItem
  * @brief �ĵ��б����UI��
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/12/15
  */
class DocItem : public ui::ListContainerElement
{
public:
	friend class DocForm;
	DocItem();
	virtual ~DocItem();

	/**
	* �ؼ��ڲ���ʼ��
	* @return void	�޷���ֵ
	*/
	virtual void InitControls();

	/**
	* ��ʼ���ؼ���Ϣ
	* @param[in] info �ĵ���Ϣ
	* @param[in] upload_id �ĵ��ϴ�id
	* @return void	�޷���ֵ
	*/
	virtual void Init(const nim::DocTransInfo& info, const std::string& upload_id);

	/**
	* ��ȡ�ĵ�id
	* @return string �ĵ�id
	*/
	std::string GetDocId() { return doc_info_.id_; }

public:
	// ���ϴ���صĽ���ؼ�
	enum DocItemUploadState
	{
		kDocItemUploadStatePrepare = 0,
		kDocItemUploadStateUploading,
		kDocItemUploadStateTranscoding,
		kDocItemUploadStateFaild,
		kDocItemUploadStateTranscodeFaild
	};

	// ��������صĽ���ؼ�
	enum DocItemDownloadState
	{
		kDocItemDownloadStateInit = 0,
		kDocItemDownloadStateDownload,
		kDocItemDownloadStateDownloading,
		kDocItemDownloadStateRetry,
		kDocItemDownloadStateUse
	};

	/**
	* �л�������ģʽ���ϴ�ģʽ
	* @param[in] download_or_upload ����ģʽ���ϴ�ģʽ
	* @return void �޷���ֵ
	*/
	void SwitchToDownloadMode(bool download_or_upload);

	/**
	* ��ʾ�ϴ�ģʽ��ĳ����ť
	* @param[in] button ��ť����
	* @return void �޷���ֵ
	*/
	void ShowUploadUI(DocItemUploadState button);

	/**
	* ��ʾ����ģʽ��ĳ����ť
	* @param[in] button ��ť����
	* @return void �޷���ֵ
	*/
	void ShowDownloadUI(DocItemDownloadState button);

private:
	/**
	* �������ذ�ť������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBtnDownloadClick(ui::EventArgs* arg);

	/**
	* ��������ʹ�ð�ť������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBtnDownloadUseClick(ui::EventArgs* arg);

	/**
	* �����������԰�ť������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBtnDownloadRetryClick(ui::EventArgs* arg);

	/**
	* ����ɾ����ť������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBtnDeleteClick(ui::EventArgs* arg);

	/**
	* �����ϴ����԰�ť������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBtnUploadRetryClick(ui::EventArgs* arg);

	/**
	* �����ϴ�ȡ����ť������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnBtnUploadCancelClick(ui::EventArgs* arg);

private:
	/**
	* ���ý�������ʾ��ת�����
	* @param[in] value ����ֵ�����ֵ����Ϊ10000���������100���ȡ����С����İٷֱ�
	* @return void	�޷���ֵ
	*/
	void SetTranscodeProg(int value);

	/**
	* ��ʼִ��ת���еĽ���������
	* @return void	�޷���ֵ
	*/
	void StartTranscodAnimation();

	/**
	* ��ʼִ��ת����ɵĽ���������
	* @return void	�޷���ֵ
	*/
	void EndTranscodAnimation();

private:
	/**
	* �����ĵ�ҳ�Ľ���ص�����
	* @param[in] doc_id �ĵ�id
	* @param[in] page_num ���ص�ҳ��
	* @param[in] res_code ������
	* @param[in] file_path ʵ������·��
	* @param[in] call_id ����id
	* @param[in] res_id ��Դid
	* @return void	�޷���ֵ
	*/
	void OnDownlaodDocPageCallback(const std::string& doc_id, int32_t page_num, nim::NIMResCode res_code, const std::string& file_path, const std::string& call_id, const std::string& res_i);

	/**
	* ����ĵ��Ƿ�������ɵĻص�����
	* @param[in] is_downloaded �Ƿ��������
	* @return void	�޷���ֵ
	*/
	void OnCheckDocDownloadedCallback(bool is_downloaded);

	/**
	* �ĵ��ϴ���ϵĻص�����
	* @param[in] res_code ������
	* @param[in] result �ϴ���ɵĽ��
	* @return void	�޷���ֵ
	*/
	void OnDocUploadCompeleteCallback(nim::NIMResCode res_code, const nim::UploadMediaResult& result);

	/**
	* �ĵ��ϴ����ȵĻص�����
	* @param[in] completed_size �Ѿ��ϴ��Ĵ�С
	* @param[in] file_size �ϴ��ļ����ܴ�С
	* @param[in] result ������̵�����
	* @return void	�޷���ֵ
	*/
	void OnDocUploadProgressCallback(int64_t completed_size, int64_t file_size, const nim::ProgressData& data);

	/**
	* �ĵ�ת�����֪ͨ�Ļص�����
	* @param[in] code ������
	* @param[in] doc_info �ĵ���Ϣ
	* @return void	�޷���ֵ
	*/
	void OnDocInfoNotifyCallback(int32_t code, const nim::DocTransInfo& doc_info);

	/**
	* ��ʼ���ĵ�ͼƬ���ĵ�����
	* @return void	�޷���ֵ
	*/
	void InitDocImageAndTitle();

	/**
	* �����ĵ���ҳͼƬ�Ľ���ص�����
	* @param[in] doc_id �ĵ�id
	* @param[in] page_num ���ص�ҳ��
	* @param[in] res_code ������
	* @param[in] file_path ʵ������·��
	* @param[in] call_id ����id
	* @param[in] res_id ��Դid
	* @return void	�޷���ֵ
	*/
	void OnDownlaodDocImageCallback(const std::string& doc_id, int32_t page_num, nim::NIMResCode res_code, const std::string& file_path, const std::string& call_id, const std::string& res_i);

private:
	nim::DocTransInfo doc_info_;

	ui::Control		*doc_image_;
	ui::Label		*doc_title_;

	ui::TabBox		*tab_switch_;
	ui::TabBox		*tab_download_controls_;
	ui::Button		*btn_download_;
	ui::Button		*btn_download_use_;
	ui::Button		*btn_downloading_;
	ui::Button		*btn_download_retry_;

	ui::TabBox		*tab_upload_controls_;
	ui::Label		*upload_prog_tip_;
	ui::Label		*upload_error_tip_;
	ui::Button		*btn_upload_retry_;
	ui::Button		*btn_upload_cancel_;

	ui::Button		*btn_delete_;

	ui::Progress	*prog_upload_;
	ui::Progress	*prog_transcode_;

	TranscodeAnimationPlayer transcode_animation_; // ģ��ת����ȵĶ���

	AutoUnregister	unregister_cb;
};
}