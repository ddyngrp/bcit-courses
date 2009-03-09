def get_file_list():
	files = OpenFileDialog();
	socket = create_udp_socket();
	return files;


def create_udp_socket():
	socket = socket(INET_ALL, SOCKET_STREAM, UDP);
	return socket;


def wait_for_connection(socket):
	if listen(socket, SOMAXCONN) != 0:
		if busy == true:
			send(NULL, BUSY_FLAG);
			break;
		else:
			check_request_type();


def check_request_type():
	recv(socket, request, request.size, &size);

	if request == MULTICAST_STREAM:
		add_client_ip(socket.ip);
		read_file_list(files);
	else if request == OTHER:
		return get_song_list();


def add_client_ip(ip):
	list multicast;
	multicast.add(ip);


def send_busy_message(socket):
	send(NULL, BUSY_MESSAGE);


def spawn_service():
	CreateThread(NULL, 0, read_file_list, files, 0);

def read_file_list(files):
	while read_file == true:
		for i in files:
			ReadFile(files[i], fileBuff, fileBuff.size, &read);
			broadcast(fileBuff);
		

def broadcast(data):
	write_to(socket, multicast, data, &sent);


def kill_threads():
	read_file = false;
	close(socket);


def send(data, type):
	out_data = type + data; # Packetize the data
	write(socket, out_data);
