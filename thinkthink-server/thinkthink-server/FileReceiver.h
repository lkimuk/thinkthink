#pragma once
#include <boost/asio.hpp>
#include <fstream>



class FileSession 
	: public std::enable_shared_from_this<FileSession>
{
	using this_type = FileSession;
	using socket_type = boost::asio::ip::tcp::socket;
	using socket_ptr = std::shared_ptr<socket_type>;

public:
	FileSession(socket_ptr socket);

	void Start();

private:
	void ReceiveFile();

private:
	constexpr static size_t max_length = 1024;
	char m_data[max_length];
	socket_ptr m_socket;
	std::ofstream m_file;
};


class FileReceiver
{
	using socket_type   = boost::asio::ip::tcp::socket;
	using socket_ptr	= std::shared_ptr<socket_type>;
	using endpoint_type = boost::asio::ip::tcp::endpoint;
	using acceptor_type = boost::asio::ip::tcp::acceptor;

public:
	FileReceiver(uint16_t port);

	void Start();

private:
	void Accept();

private:
	boost::asio::io_context m_io;
	acceptor_type m_acceptor;
};

