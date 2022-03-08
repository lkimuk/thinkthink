#include "ThinkThinkServer.h"
#include <iostream>
#include <memory>


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

void VideoSession::DispatchMessage(const std::string& data)
{
	std::cout << data << std::endl;

	AsyncWriteMessage("response from server");
}
