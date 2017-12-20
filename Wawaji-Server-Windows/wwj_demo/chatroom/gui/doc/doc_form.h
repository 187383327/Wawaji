#pragma once

namespace nim_chatroom
{

class DocItem;
/** @class DocForm
  * @brief �ĵ��ⴰ��
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/12/15
  */
class DocForm : public nim_comp::WindowEx
{
public:
	DocForm();
	~DocForm();

	//�����麯��
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const override;
	virtual UINT GetClassStyle() const override;

	/**
	* ���ڳ�ʼ������
	* @return void	�޷���ֵ
	*/
	virtual void InitWindow() override;

	/**
	* �������пؼ�������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	virtual bool OnClicked(ui::EventArgs* msg);

	/**
	* �����ĵ��б��������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnDocListScroll(ui::EventArgs* msg);

	/**
	* �����ļ�·����ȡ�ĵ��ϴ���Ϣ
	* @param[in] file_path �ļ�·��
	* @param[out] out_file_path �ļ�·��
	* @param[out] out_file_name �ļ���
	* @param[out] out_file_type �ļ�����
	* @return bool true �ϴ���Ϣ��Ч��false �ϴ���Ϣ��Ч
	*/
	static bool GetUploadFileInfo(const std::wstring& file_path, std::string& out_file_path, std::string& out_file_name, nim::NIMDocTranscodingFileType& out_file_type);
	
	/**
	* ���ļ���չת��Ϊ�ĵ�����
	* @param[in] file_ext ��չ��
	* @return int �ĵ����ͣ�0������Ч
	*/
	static int GetFileType(std::wstring file_ext);
public:
	static const LPTSTR kClassName;

private:
	/**
	* �ڵ������ļ�ѡ�񴰿���ѡ����ĳ���ļ�
	* @param[in] ret �Ƿ�ѡ�����ļ�
	* @param[in] file_path �ļ�·��
	* @return void	�޷���ֵ
	*/
	void OnDocFileSelected(BOOL ret, std::wstring file_path);

	/**
	* �����ϴ�id���ĵ���Ϣ���ĵ��б��д���һ���µ��ĵ��б���ؼ�
	* @param[in] upload_id �ϴ�id
	* @param[in] file_path �ļ�·��
	* @param[in] file_name �ļ���
	* @param[in] file_type �ļ�����
	* @return DocItem* �ĵ��б���ؼ�
	*/
	DocItem* CreateStartUploadDocItem(const std::string& upload_id, const std::string& file_path, const std::string& file_name, nim::NIMDocTranscodingFileType file_type);
private:

	/**
	* ��ȡ�ĵ���Ϣ�Ļص�����
	* @param[in] count ������������
	* @param[in] doc_infos �ĵ���Ϣ
	* @return void	�޷���ֵ
	*/
	void OnGetDocInfosCallback(int32_t count, const std::list<nim::DocTransInfo>& doc_infos);

	/**
	* �ĵ�ת�����֪ͨ�Ļص�����
	* @param[in] code ������
	* @param[in] doc_info �ĵ���Ϣ
	* @return void	�޷���ֵ
	*/
	void OnDocInfoNotifyCallback(int32_t code, const nim::DocTransInfo& doc_info);

private:
	ui::ListBox		*doc_list_;
	int32_t			doc_count_;
	bool			is_getting_docs_info_;
	AutoUnregister	unregister_cb;
};

}