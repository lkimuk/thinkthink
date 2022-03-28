#include "FileReceiver.h"
#include <iostream>
#include <filesystem>
#include <cstring>



FileReceiver::FileReceiver(uint16_t port)
	: m_acceptor(m_io, endpoint_type(boost::asio::ip::tcp::v4(), port))
{
}

void FileReceiver::Start()
{
	Accept();

	m_io.run();
}

void FileReceiver::Accept()
{
	socket_ptr socket(new socket_type(m_io));
	m_acceptor.async_accept(*socket,
		[this, socket](const boost::system::error_code& ec) {
			if (!ec) {
				std::cout << "connected file client: " << socket->remote_endpoint().address() << '\n';

				std::make_shared<FileSession>(socket)->Start();
			}

			Accept();
		});
}


FileSession::FileSession(socket_ptr socket)
	: m_socket(socket)
{
}

void FileSession::Start()
{
	ReceiveFile();
}

void FileSession::ReceiveFile()
{
	memset(m_data, 0, max_length);
	static bool is_header = true;
	static size_t count = 0;
	static size_t total = 0;

	auto self(shared_from_this());
	m_socket->async_read_some(boost::asio::buffer(m_data),
		[this, self](boost::system::error_code ec, std::size_t bytes) {
			if (!ec) {
				if (is_header) {
					// 解析文件头部长度
					auto start_of_file = std::strstr(m_data, "SOF");
					auto end_of_file = std::strstr(m_data, "EOF");
					auto header_length = end_of_file - start_of_file + 3;

					// 解析文件长度
					auto start_of_length = std::strstr(m_data, "SOL");
					auto end_of_length = std::strstr(m_data, "EOL");
					start_of_length += 3;
					char* file_length = (char*)malloc(end_of_length - start_of_length + 1);
					memcpy(file_length, start_of_length, end_of_length - start_of_length);
					file_length[end_of_length - start_of_length] = '\0';
					total = atoi(file_length);
					free(file_length);

					// 解析文件类型
					auto start_of_type = std::strstr(m_data, "SOT");
					auto end_of_type = std::strstr(m_data, "EOT");
					start_of_type += 3;
					char* file_type = (char*)malloc(end_of_type - start_of_type + 1);
					memcpy(file_type, start_of_type, end_of_type - start_of_type);
					file_type[end_of_type - start_of_type] = '\0';

					// 创建目录
					namespace fs = std::filesystem;
					fs::path p("file_recv/");
					fs::create_directories(p);
					char file_name[MAX_PATH] = "file_recv/123.";
					strcat_s(file_name, file_type);
					
					// 打开文件
					m_file.open(file_name, std::ios::out | std::ios::binary | std::ios::trunc);
					if (!m_file.is_open())
						throw std::runtime_error("cannot open file to write");

					free(file_type);

					// 实际文件
					is_header = false;
					if (bytes != header_length) {
						bytes -= header_length;
						memcpy(m_data, m_data + header_length, bytes);
					}
					else {
						ReceiveFile();
						return;
					}					
				}

				count += bytes;
				m_file.write(m_data, bytes);
				int percent = (count * 100 / total);
				std::cout << "current percent: " << percent << "%  ";
				std::cout << "current count: " << count << " total:" << total << "\n";

				if (count >= total) {
					std::cout << "save file successful\n";
					m_socket->close();
					m_file.close();
					return;
				}

				ReceiveFile();
			}
		});
}
