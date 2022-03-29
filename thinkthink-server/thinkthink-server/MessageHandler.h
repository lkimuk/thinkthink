#pragma once
#include "pugixml.hpp"
#include "okdp/utils/function_traits.hpp"
#include "okdp/utils/delegate.hpp"
#include <string>


struct ResponseMessage {
	ResponseMessage();

	void SetMessage(const char* key, const char* value);

	std::string GetData();

private:
	pugi::xml_document m_doc;
};

struct RequestMessage {
	RequestMessage(const std::string& data);

	// ��ȡ��Ϣֵ
	std::string GetValue(const char* key) const;

	// ��ȡ��Ϣ����
	std::string GetType() const;

	// ��ȡԭʼ��Ϣ�ı�
	std::string GetRawData() const;

private:
	std::shared_ptr<pugi::xml_document> m_doc;
};


class MessageHandler
{
	using callback_type = std::function<void(RequestMessage)>;
	using delegate_type = okdp::utils::delegate<std::string, callback_type>;

public:
	void SetHandler(const char* type, callback_type callback);
	
	template<typename F, typename T, typename... Args>
	void SetHandler(const std::string& type, const F& f, T&& head, Args&&... args) {
		m_delegate.insert(type, mc::binder<callback_type>(f, 
					std::forward<T>(head), std::forward<Args>(args)...));
	}

	// �ַ���Ϣ
	void Dispatch(const RequestMessage& request);

private:
	delegate_type m_delegate;
};

