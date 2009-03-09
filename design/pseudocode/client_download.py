def check_request_type(request):
	if request == MULTICAST_STREAM:
		socket = create_udp_socket();
		CreateThread(NULL, 0, read_udp_socket, socket, 0, 0);
	else if request == OTHER:
		return get_song_list();


def create_udp_socket():
	socket = socket(INET_ALL, SOCKET_STREAM, UDP);
	return socket;


def read_udp_socket(socket):
	while read_udp == true:
		if recv(socket, buffer, buffer.size, 0) != 0:
			break;


def play_buffer(buffer):
	while play == true:
		tmpBuffer = buffer;
		PlaySound(tmpBuffer);


def kill_threads():
	read_udp == false;
	play == false;
	close(socket);


def get_song_list:
	list song_list = send (NULL, REQ_SONG_LIST);
	return song_list;


def send_song_choice():
	list chosen_songs;
	for i in song_list:
		if song_list[i] == selected:
			chosen_songs.add(song_list[i]);

	if gui_stream == selected:
		req_type = STREAM;
	else:
		req_type = DOWNLOAD;

	send (chosen_songs, req_type);


def spawn_service():
	socket = create_tcp_socket();
	CreateThread(NULL, 0, read_tcp_socket, socket, 0);

def create_tcp_socket():
	socket = socket(INET_ALL, SOCKET_STREAM, TCP);
	return socket;


def read_tcp_socket(socket):
	file = CreateFile(file_name, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	while true:
		if recv(socket, buffer, buffer.size, &size) != 0:
			WriteFile(file, buffer, size, &written, NULL);
		else:
			break; # end the loop
	
	close(file);


def send(data, type):
	out_data = type + data; # Packetize the data
	write(socket, out_data);
