#include "ThinkThinkServer.h"
#include <iostream>
#include <memory>



ThinkThinkServer::ThinkThinkServer(uint16_t port)
	: m_acceptor(m_io, endpoint_type(ip::tcp::v4(), port))
{
}

void ThinkThinkServer::Accept()
{
	socket_ptr socket(new socket_type(m_io));
	m_acceptor.async_accept(*socket,
		[this, socket](const boost::system::error_code& ec) {
			if (!ec) {
				std::cout << "connected client: " << socket->remote_endpoint().address() << '\n';

				std::make_shared<VideoSession>(socket)->Start();
			}

			Accept();
	});
}

void ThinkThinkServer::Run()
{
	m_io.run();
}

VideoSession::VideoSession(socket_ptr socket)
	: m_socket(socket)
{
	m_MessageHandler.SetHandler("GetVideoCategories", &VideoSession::OnGetVideoCategories, this);
}

void VideoSession::Start()
{
	AsyncReadMessage();
}

void VideoSession::AsyncReadMessage()
{
	memset(m_data, 0, max_length);

	auto self(shared_from_this());
	m_socket->async_read_some(buffer(m_data),
		[this, self](boost::system::error_code ec, std::size_t) {
			if (!ec) {
				DispatchMessage(m_data);
			}
	});
}

void VideoSession::AsyncWriteMessage(const std::string& res)
{
	auto self(shared_from_this());
	m_socket->async_write_some(buffer(res.data(), res.length()),
		[this, self](boost::system::error_code ec, std::size_t) {
			if (!ec) {
				AsyncReadMessage();
			}
	});
}

// 分发消息
void VideoSession::DispatchMessage(const std::string& data)
{
	RequestMessage request(data);
	m_MessageHandler.Dispatch(request);
}

// 获取目录消息
void VideoSession::OnGetVideoCategories(const RequestMessage& request)
{
	ResponseMessage response;
	sql_type mysql;
	mysql.connect("127.0.0.1", "root", "", "thinkthink");
	mysql.execute("SET NAMES GB2312");
	auto categories = mysql.query<VideoCategory>();
	for (auto& category : categories) {
		response.SetMessage("Category", category.category_name.c_str());
	}

	AsyncWriteMessage(response.GetData());
}
