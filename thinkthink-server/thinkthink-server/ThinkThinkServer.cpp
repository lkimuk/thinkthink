#include "ThinkThinkServer.h"
#include <iostream>
#include <memory>
#include "FileReceiver.h"



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
	m_MessageHandler.SetHandler("GetVideos", &VideoSession::OnGetVideos, this);
	m_MessageHandler.SetHandler("GetUploaderName", &VideoSession::OnGetUploaderName, this);
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
		[this, self](boost::system::error_code ec, std::size_t bytes) {
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

void VideoSession::OnGetVideos(const RequestMessage& request)
{
	auto category = request.GetValue("VideoCategory");
	sql_type mysql;
	mysql.connect("127.0.0.1", "root", "", "thinkthink");
	mysql.execute("SET NAMES GB2312");
	auto videos = mysql.query<Video>();

	pugi::xml_document doc;
	pugi::xml_node root = doc.append_child("ThinkThink");
	root.append_child("ResponseType").text().set("GetVideos");
	for (auto video : videos) {
		std::cout << video.video_name << " " << video.category << '\n';
		if (video.category == category) {
			pugi::xml_node v = root.append_child("Video");
			v.append_child("Id").text().set(video.video_id.c_str());
			v.append_child("Name").text().set(video.video_name.c_str());
			v.append_child("Uploader").text().set(video.uploader.c_str());
			v.append_child("CoverImage").text().set(video.cover_image.c_str());
			v.append_child("Describe").text().set(video.describe.c_str());
			v.append_child("UploadDate").text().set(video.upload_date.c_str());
			v.append_child("Source").text().set(video.source.c_str());
		}
	}

	std::stringstream ss;
	doc.save(ss, "");
	std::cout << ss.str() << '\n';

	AsyncWriteMessage(ss.str());
}

void VideoSession::OnGetUploaderName(const RequestMessage& request)
{
	std::cout << request.GetValue("UploaderId");

	AsyncWriteMessage("echo message");
}
