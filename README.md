# Basic-iotNetwork-2024
부경대학교 2024 IoT 개발자 과정 iot 네트워크 프로그래밍 리포지토리

## 1일차(24.06.11)
- 네트워크 프로그래밍과 소켓의 이해
    - IPv4
        - 내 컴퓨터의 인터넷 주소
        - 4개의 byte로 구성되어 있음
        - IPv6 : IPv6로 제공가능한 인터넷 주소가 모두 할당되었을 때 대체하여 사용할 IP주소
        - 기본 게이트웨이 : 내 컴퓨터로 들어오는 출입문
    - 전송방식(TCP/UDP)
        - TCP(전송 제어 프로토콜) : 정확하게 데이터를 전송하는게 필요할 때
        - UDP(사용자 데이터그램 프로토콜)
            - 보안과 신뢰성보다 전송 속도와 효율성이 더 중요한 경우 데이터를 전송하기 위해 IP과 함께 오래 사용된 프로토콜
            - 대용량으로 데이터를 전송할 때 조금은 누락되어도 괜찮을 때

    - 네트워크 프로그래밍에대한 간단한 이해(**소말리아**)
        - 소 : 소켓(socket)
            - 물리적으로 연결된 네트워크 상에서의 데이터 송수신에 사용할 수 있는 소프트웨어 장치 
            - 휴대폰 기기 
        - 말 : 바인드(Bind) 
            - IP주소와 PORT번호 할당 
            - 개통을 위한 전화번호
        - 리 : 리슨(Listen) 
            - 연결요청 가능상태로 변경 
            - 개통이 완료된 상태
        - 아 : 엑셉트(Accept) 
            - 연결요청에 대한 수락 
            - 개통이 완료된 후 다른 상대방과 통화를 하는 것

    - 리눅스 기반 파일 조작하기
        - 파일 디스크립터
            - 시스템으로부터 할당 받은 파일 또는 소켓에 부여된 정수
            - 일반적으로 파일과 소켓은 생성의 과정을 거쳐야 파일 디스크립터가 할당
            - 0 : 표준입력(Standard Input)
            - 1 : 표준출력(Standard Output)
            - 2 : 표준에러(Standard Error)

        - 파일 열기
            - int open(const char *path, int flag);
            - 성공 시 파일 디스크립터, 실패 시 -1 반환
            - open : 파일이름, flag : 파일의 오픈 모드

            - 파일의 오픈 모드
                - O_CREAT : 필요하면 파일을 생성
                - O_TRUNC : 기존 데이터 전부 삭제
                - O_APPEND : 기존데이터를 보존하고, 뒤에 이어서 저장
                - O_RDONLY : 읽기 전용으로 파일 오픈
                - O_WRONLY : 쓰기 전용으로 파일 오픈
                - O_RDWR : 읽기 쓰기 겸용으로 파일 오픈

            - 파일 권한
                - 1 : 실행, 2 : 쓰기, 4 : 읽기
                - 000X(넷째 자리) : 기타사용자, 00X0(셋째 자리) : 그룹, 0X00(둘째 자리) : 사용자
                - S_IRWXU, S_IRUSR, S_IWUSR, S_IXUSR : 사용자에게 각각 전체권한, 읽기 권한, 쓰기 권한, 실행 권한 부여
                - S_IRWXG, S_IRGRP, S_IWGRP, S_IXUSR : 그룹에게 각각 전체권한, 읽기 권한, 쓰기 권한, 실행 권한 부여
                - S_IRWXO, S_IROTH, S_IWOTH, S_IXOTH : 기타 사용자에게 각각 전체권한, 읽기 권한, 쓰기 권한, 실행 권한 부여

        - 파일 닫기
            - int close(int fd);
            - 성공 시 0, 실패 시 -1
            - fd : 닫고자하는 파일 또는 소켓의 파일 디스크립터

        - 파일에 데이터 쓰기
            - ssize_t write(int fd, const void * buf, size_t nbytes);
            - 성공시 전달한 바이트 수, 실패 시 -1
            - fd : 데이터 전송대상의 파일 디스크립터, buf : 전송할 데이터가 저장된 버퍼의 주소값, nbyte : 전송할 데이터의 바이트 수

        - 파일 읽기
            - ssize_t read(int fd, void *buf, size_t nbyte);
            - 성공 시 수신한 바이트 수(단 파일의 끝을 만나면 0), 실패 시 -1
            - fd : 파일 디스크립터, buf : 수신한 데이터를 저장할 버퍼의 주소 값 전달, nbytes : 수신할 최대 바이트 수

- 소켓의 타입과 프로토콜의 설정
    - 소켓의 프로토콜
        - 프로토콜의 개념 : 컴퓨터 상호간의 대화에 필요한 통신규약
        - 소켓의 생성
            - int socket(int domain, int type, int protocol)
            - domain : 소켓이 사용할 프로토콜 체계 정보 전달
            - type : 소켓의 데이터 전송방식에 대한 정보 전달
            - protocol : 두 컴퓨터간 통신에 사용되는 프로토콜 정보 전달

        - 프로토콜 체계(Protocol Family)
            - PF_INET : IPv4 인터넷 프로토콜 체계
            - PF_INET6 : IPv6 인터넷 프로토콜 체계
            - PF_LOCAL : 로컬 통신을 위한 UNIX 프로토콜 체계
            - PF_PACKET : Low Level 소켓을 위한 프로토콜 체계
            - PF_IPX : IPX 노벨 프로토콜 체계

        - 소켓의 타입(Type)
            - 연결지향형 소켓(SOCK_STREAM) -> TCP
                - 신뢰성 있는 순차적인 바이트 기반의 연결지향 데이터 전송 방식의 소켓
                - 전송되는 데이터에 경계가 존재하지 않음
                - 소켓 대 소켓의 연결은 반드시 1대1 이어야하 얌

            - 비연결지향형 소켓(SOCK_DGRAM) -> UDP
                - 신뢰성과 순차적 데이터 전송을 보장하지 않는, 고속의 데이터 전송을 목적으로 하는 소켓
                - 전송되는 데이터의 경계가 존재, 한번에 전송할 수 있는 데이터가 제한됨

        - 프로토콜 최종선택
            - 최종적으로 소켓이 사용하게 될 프로토콜 정보를 전달하는 목적
            - 대부분의 경우 0을 전달하더라도 원하는 소켓 생성 가능
            - 하나의 프로토콜 체계 안에 데이터 전송방식이 동일한 프로토콜이 둘 이상 존재하는 경우 
                -> 소켓으 데이터 전송 방식은 같지만, 그 안에서도 프로토콜이 나뉘는 상황이 발생할 경우
                -> 0이 아닌 별도의 프로토콜 지정 필요
            - IPv4 인터넷 프로토콜 체계에서 동작하는 연결지향형 데이터 전송 소켓

            ```c
                int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
            ```

            - IPv4 인터넷 프로토콜 체계에서 동작하는 비 연결지향형 데이터 전송 소켓

            ```c
                int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
            ```
- 주소체계와 데이터 정렬
    - IP주소와 PORT번호
        - IP주소 : 데이터 송수신을 위해 컴퓨터에 부여하는 값
        - PORT번호 : 컴퓨터에게 부여하는 값이 아닌, 프로그램 상에서 생성되는 소켓을 구분하기 위해 소켓에 부여되는 번호
        <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet001.png">

    - 주소정보의 표현
        - IPv4 기반의 주소표현을 위한 구조체

        ```c
            struct sockaddr_in
            {
                sa_family_t     sin_family;     // 주소체계
                unit16_t        sin_port;       // 16비트 TCP/UDP 포트번호  -> 네트워크 바이트 순서로 저장
                struct in_addr  sin_addr;       // 32비트 IP주소 -> 네트워크 바이트 순서로 저장
                char            sin_zero[8];    //  현재는 사용되지 않음 -> IPv6를 위해 임의로 만들어둔 배열
            }

            struct in_addr
            {
                in_addr_t       s_addr;         // 32비트 IPv4 인터넷 주소
            }
        ```
        - POSIX 정의 자료형
            - POSIX : 유닉스 계열의 운영체제에 적용하기 위한 표준
            - int8_t, unit8_t, int16_t, unit16_t, int32_t, uint32_t -> u가 있을경우 unsigned(양수만 가능)
            - sa_family_t : 주소체계, socklen_t : 길이정보
            - in_addr_t : IP주소정보, in_port_t : PORT 번호정보

        - sin_family
            - AF_INET : IPv4 인터넷 프로토콜
            - AF_INET : IPv6 인터넷 프로토콜
            - AF_LOCAL : 로컬 통신을 위한 유닉스 프로토콜

    - 네트워크 바이트 순서와 인터넷 주소 변환
        - 바이트 순서와 네트워크 바이트 순서
            - 빅 엔디안(Big Endian)
                - 하위 바이트의 값을 큰 번지(제일 오른쪽)에 저장
                - 상위 바이트의 값을 작은 번지(제일 왼쪽)에 저장
            - 리틀 엔디안(Little Endian)
                - 하위 바이트으 값을 작은 번지(제일 왼쪽)에 저장
                - 상위 바이트의 값을 큰 번지(제일 오른쪽)에 저장

            <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet002.png">

            

        - 바이트 순서의 변환
            - htons, ntohs, htonl, ntohl
            - h : 호스트, n : 네트워크, s : short형 데이터, l : long형 데이터
            - htons : short형 데이터를 호스트 바이트 순서에서 네트워크 바이트 순서로 변환

    - 인터넷 주소의 초기화와 할당
        - 문자열 정보를 네트워크 바이트 순서로 변환
            - inet_addr 함수
                - 10진수로 표현된 문자열을 32비트 정수형태로 변환
                - IP 주소에 대한 오류검출 능력도 보유

                ```c
                #include <arpa/inet.h>
                in_addr_t inet_addr(const char * string);
                // 성공시 빅 엔디안으로 변환된 32비트 정수값, 실패 시 INADDR_NONE 반환
                ```

            - inet_aton 함수
                - 기능상으로는 inet_addr과 유사
                - 구조체 변수 in_addr를 이용하는 형태 
                    -> 변환된 IP 주소를 구조체 sockaddr_in에 선언되어있는 addr_in 구조체 변수에 대입하는 과정이 필요X

                ```c
                #include <arpa/inet.h>
                int inet_aton(const char * string, struct in_addr * addr);
                // string : 변환할 IP 주소 정보를 담고있는 문자열의 주소값, addr : 변환된 정보를 저장할 in_addr 구조체 변수의 주소 값 전달
                // 성공 시 1(true), 실패 시 0(false) 반환
                ```

## 2일차(24.06.12)
- 주소체계와 데이터 정렬
    - 인터넷 주소의 초기화와 할당
        - 정수형태의 IP 정보를 문자열 형태의 IP정보로 변환
            - inet_ntoa 함수
                - 
            ```c
            #include <arpa/inet.h>
            char * inet_ntoa(struct in_addr adr);
            // 성공 시 반환된 문자열의 주소값
            ```

        - 인터넷 주소의 초기화
            - memset 함수
                - 구조체 변수의 멤버들을 초기화하는 함수

                ```c
                memset(&addr, 0, sizeof(addr)); // 구조체 변수 addr의 모든 멤버 0으로 초기화
                // 0으로 초기화하는 이유 : 구조체 멤버 sin_zero를 0으로 초기화 하기 위함
                ```

        - INADDR_ANY
            - 소켓이 동작하는 컴퓨터의 IP주소가 자동으로 할당되어 IP주소를 직접 입력하는 수고를 절감

            ```c
                memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = htonl(INADDR_ANY);
                addr.sin_port=htons(atoi(serv_port));
            ```

        - 소켓에 인터넷 주소 할당하기
            - bind 함수
            
            ```c
            #include <sys/socket.h>
            int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen)
            // sockfd : 소켓의 파일 디스크립터, myaddr : 할당당하고자 하는 주소정보를 지니는 구조체 변수의 주소값, addrlen : 구조체 변수의 길이정보
            // 성공시 0, 실패시 -1 반환
            ```

- TCP 기반 서버/클라이언트 1
    - TCP와 UDP에 대한 이해
        - TCP/IP 프로토콜 스택

            <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet003.png">

            - LINK 계층
                - 물리적인 영역의 표준화에 대한 결과(물리적인 연결)
                - LAN, WAN, MAN과 같은 네트워크 표준과 관련된 프로토콜을 정의하는 영역.

            - IP 계층
                - 목적지로 데이터를 전송하기 위한 경로
                - 하나의 데이터 패킷이 전송되는 과정에만 중점
                - IP 자체는 비 연결지향적이며 신뢰할 수 없는 프로토콜이기
                - 데이터 손실 또는 오류 발생 문제 가능성

            - TCP/UDP 계층
                - IP 계층에서 알려준 경로 정보를 바탕으로 실제 데이터를 송수신을 담당하는 '전송(Transport) 계층'
                - TCP
                    - 데이터가 무사히 전달되었는지 확인하여 신뢰성 있는 데이터 전송을 담당
                    - 분실된 데이터에 대해 재전송을 요청
    
    - TCP기반 서버, 클라이언트 구현
        - TCP 서버에서의 기본적인 함수 호출 순서
            - socket() -> bind() -> listen() -> accept() -> read()/write() -> close()

        - 연결요청 대기 상태로의 진입(listen 함수)
            - 클라이언트가 서버의 서버 소켓에 연결요청을 하고 연결요청 대기큐에서 대기상태로 진입

            ```c
            #include <sys/socket.h>
            int listen(int sock, int backlog);
            // sock : 연결요청 대기상태에 두고자 하는 소켓의 파일 디스크립터 -> 서버소켓
            // backlog : 연결요청 대기 큐(Queue)의 크기정보
            // 성공시 0, 실패시 -1
            ```

        - 클라이언트의 연결 요청 수락(**accept 함수**)
            - '연결요청 대기 큐'에서 대기중인 클라이언트의 연결요청 수락
            - 호출 성공 시 내부적으로 데이터 입출력에 사용할  클라이언트 소켓을 생성하고, 그 소켓의 파일 디스크립터 반환

            ```c
            #include <sys/socket.h>
            int accept(int sock, struct sockaddr * addr, socklen_t * addrlen);
            // sock : 서버 소켓의 파일 디스크립터
            // addr : 연결 요청을 한 클라이언트의 주소정보를 담을 변수의 주소값
            // addrlen : addr에 전달된 주소의 변수 크기(바이트 단위)
            // 성공 시 생성된 소켓의 파일 디스크립터, 실패 시 -1
            ```
        
        - TCP 클라이언트의 기본적인 함수 호출 순서
            - socket() -> connect() -> read()/write() -> close()
            - connect 함수

            ```c
            #include <sys/socket.h>
            int connect(int sock, struct sockaddr * servaddr, socklen_t addrlen);
            // sock : 클라이언트 소켓의 파일 디스크립터
            // servaddr : 연결 요청 할 서버의 주소정보를 담은 변수의 주소값
            // addrlen : servaddr에 전달된 주소의 변수 크기(바이트 단위)
            // 성공 시 0, 실패 시 -1
            ```
        
        - TCP 기반 서버, 클라이언트의 함수호출 관계

        <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet004.png">

- TCP 기반 서버/클라이언트 2
    - TCP
        - 입출력 버퍼
            - write 함수가 호출되는 순간 데이터는 출력 버퍼로 이동
            - read 함수가 호출되는 순간 입력버퍼에 저장된 데이터를 읽어들임
            - 입력 버퍼의 크기를 초과하는 분량의 데이터 전송은 발생하지 않음

        - TCP 내부의 동작원리
            - 상대 소켓과의 연결(Three-way handshaking)
            - 상대 소켓과의 데이터 송수신
            - 상대 소켓과의 연결 종료

        <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet005.png">

- UDP 기반 서버/클라이언트
    - UDP에 대한 이해
        - TCP와 달리 흐름제어를 하지 않는 데이터 전송 방식

    - UDP 기반 서버/클라이언트의 구현
        - UDP에서는 서버와 클라이언트의 연결설정 과정이 필요없음
        - 서버건 클라이언트 건 하나의 소켓만 있으면 됨
        - 데이터를 전송할 때 마다 반드시 목적지의 주소정보를 별도로 추가해야함
        - sendto 함수

        ```c
        #include <sys/socket.h>
        ssize_t sendto(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *to, socklen_t addr len);
        // 성공 시 전송된 바이트 수, 실패 시 -1 반환
        // sock : 데이터 전송에 사용될 UDP 소켓의 파일 디스크립터
        // buff : 전송할 데이터가 저장된 버퍼의 주소값
        // nbytes : 전송할 데이터 크기
        // flags : 옵션 지정에 필요한 매개변수
        // to : 목적지 주소정보를 담고있는 sockaddr 구조체 변수
        // addrlen : to로 전달하는 구조체 변수 크기 지정
        ```
        - recvfrom함수

        ```c
        #include <sys/socket.h>
        ssize_t sendto(int sock, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t addr len);
        // 성공 시 수신한 바이트 수, 실패 시 -1 반환
        // sock : 데이터 수신에 사용될 UDP 소켓의 파일 디스크립터
        // buff : 데이터 수신에 사용될 저장된 버퍼의 주소값
        // nbytes : 수신할 최대 바이트 수
        // flags : 옵션 지정에 필요한 매개변수
        // from : 발신지 주소정보를 담고있는 sockaddr 구조체 변수
        // addrlen : from으로 전달하는 구조체 변수 크기 지정   
        ```


## 3일차(24.06.13)
- UDP 기반 서버/클라이언트
    - UDP의 데이터 송수신 특성과 connect 함수 호출
        - 데이터 송수신 과정에서 입력함수의 호출횟수와 출력함수의 호출횟수가 완벽하게 일치해야함
        - connected 소켓 : 목적지 정보가 등록되어 있는 소켓
        - unconnected 소켓 : 목적지 정보가 등록되어 있지 않은 소켓
        - UDP 소켓은 기본적으로 unconnected 소켓이나 하나의 호스트와 오랜 시간 데이터를 송수신할 경우 connected  소켓으로 만드는 것이 효율적
        - connected UDP 소켓은 sendto, recvfrom 함수가 아닌 write, read 함수로도 데이터 송수신 가능    

- 소켓의 종료
    - TCP 기반의 Half-close
        - 일반적인 연결종료의 문제점
            - Linux의 close함수호출과 Window의 closesocket 함수호출은 완전종료를 의미
            - Half-close : 전송 가능, 수신 불가능 or 전송 불가능, 수신 가능
            - shutdown 함수

            ```c
            #include <sys/socket.h>
            int shutdown(int sock, int howto);
            // 성공 시 0, 성공 시 -1 반환
            // sock : 종료할 소켓의 파일 디스크립터
            // howto : 종료방법
            //SHUT_RD(입력 스트림 종료), SHUT_WR(출력 스트림 종료), SHUT_RDWR(입출력 스트림 종료)
            ```

- 도메인과 인터넷 주소
    - Domain Name System
        - 도메인 이름(Domain Name) : 네트워크 상 컴퓨터를 식별하는 호스트명, 도메인 레지스트리에게서 등록된 이름(가상의 주소)
        - DNS(Domain Name System) : 도메인 이름을 IP 주소로 변환하는 것을 담당(가상의 주소 -> 실제 주소)

    - IP주소와 도메인 이름 사이의 변환
        - 도메인 이름의 필요성
            - IP주소는 도메인 이름에 비해 상대적으로 변경될 확률이 높음
            - 도메인 이름은 등록되면 평생 유지됨
            - 도메인 이름을 근거로 IP 주소를 얻어오면 서버의 IP주소로 부터 클라이언트 프로그램은 자유로워짐

        - gethostbyname함수
            - 문자열 형태의 도메인 이름으로부터의 IP의 주소정보 획득 가능
            
            ```c
            #include <netdb.h>
            struct hostent * gethostbyname(const char * hostname);
            // 성공 시 hostnet 구조체 변수 주소 값, 실패 시 NULL 포인터
            ```
        - hostnet 구조체
            
            ```c
            struct hostent
            {
                char * h_name;          // 공식 도메인 이름
                char ** aliases;        // 공식 도메인 이름 이외의 다른 도메인 이름
                int h_addrtype;         // IP주소의 주소체계에 대한 정보
                int h_length;           // 함수 호출 결과로 변환된 IP주소의 크기정보(IPv4:4, IPv6:16) 
                char ** h_addr_list;    // 해당 도메인 이름에 대응하는 IP주소들의 배열
            }
            ```
        - gethostbyname 함수
            - IP 주소를 이용해서 도메인 정보를 얻어올 때 호출
            
            ```c
            #include <netdb.h>
            struct hostent * gethostbyaddr(const char * addr, socklen_t len, int family);
            // 성공 시 hostent 구조체 변수의 주소 값, 실패 시 NULL 포인터 변환
            // addr : IP 주소정보
            // len : addr의 길이
            // family : 주소체계(AF_INET, AF_INET6)
            ```

- 소켓의 다양한 옵션
    - 소켓의 옵션과 입출력 비퍼의 크기
        - 소켓의 옵션
            - SOL_SOCKET : 소켓에 대한 일반적인 옵션
            - IPPROTO_IP : IP 프로토콜 관련 사항
            - IPPROTO_TCP : TCP 프로토콜 관련 사항
        
        - getsockopt & setsockopt 함수
            - 소켓 옵션의 설정상태 참조(Get) 및 변경(Set)

            ```c
            #include <sys/socket.h>
            int getsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);
            // 성공 시 0, 실패 시 -1
            ```
            ```c
            #include <sys/socket.h>
            int setsockopt(int sock, int level, int optname, void *optval, socklen_t *optlen);
            ```
    - SO_REUSEADDR
        - Time-wait : 연결 종료 시 마지막 패킷 전송 실패를 대비하기 위한 상태

    - TCP_NODELAY
        - Nalge알고리즘
            - 앞서 전송한 데이터에 대한 ACK를 받아야만 다음 데이터를 전송하는 알고리즘
            - 기본적으로 TCP 소켓은 Nagle알고리즘을 적용하여 데이터를 전송
            - Nagle 알고리즘의 적용 여부에 따른 트래픽의 차이가 크지 않으면서도 적용하는 것보다 데이터 전송이 빠른 경우 알고리즘 중단
            <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet006.png">

- 멀티 프로세스 서버 구현
    - 다중접속 서버의 구현 방법
        - 멀티프로세스 기반 서버 : 다수의 프로세스를 생성하는 방식으로 서비스 제공 -> 각각의 프로세스가 별도의 메모리 공간을 할당받음
        - 멀티플렉싱 기반 서버 : 입출력 대상을 묶어서 관리하는 방식으로 서비스 제공
        - 멀티쓰레딩 기반 서버 : 클라이언트의 수만큼 쓰레드를 생성하는 방식으로 서비스 제공

    - 프로세스의 이해
        - 메모리 공간을 차지한 상태에서 실행중이 프로그램
        - 프로세스 ID(PID) 
            - 모든 프로세스는 생성되는 형태에 상관없이 운영체제로 부터 ID를 부여받음
            - 2 이상의 정수형태, 숫자 1은 운영체제가 실행되자 마자 실행되는 프로세스에 할당

        - fork 함수
            - 프로세스의 생성을 위한 함수
            - 호출한 프로세스의 복사본
            - 원본가 복사본 모두 fork 함수 호출 이후 문장을 실행
            - 부모 프로세스 : 원본 프로세스 -> fork 함수의 반환값 : 자식 프로세스의 ID
            - 자식 프로세스 : 부모 프로세스를 통해 복사된 프로세스 -> fork 함수의 반환값 : 0

            ```c
            #include <unistd.h>
            pid_t fork(void);
            // 성공 시 프로세스 ID, 실패 시 -1 반환
            ```
    - 프로세스와 좀비 프로세스
        - 좀비(Zombie) 프로세스
            - 실행이 완료되었지만 여전히 프로세스 테이블에 항목이 있는 프로세스
            - 좀비 프로세스 생성 이유 : 자식프로세스를 제대로 소멸되지 않은 경우
            - 소멸 방법 : 부모프로세스가 자식프로세스의 전달값(종료했다는 신호)을 요청해야함.
            - LINUX 프로세스 확인 명령어 : ps au

## 4일차(24.06.14)
- 멀티 프로세스 서버 구현
    - 프로세스와 좀비 프로세스
        - 좀비 프로세스 소멸 방법1 : wait 함수
            - WIFEXITED : 자식 프로세스가 정상 종료된 경우, 참(true)을 반환
            - WEXITSTATUS : 자식 프로세스의 전달 값을 반환
            - 호출된 시점에서 종료된 자식 프로세스가 없을 경우, 임의으 자식 프로세스가 종료될 때 까지 블로킹(Blocking)상태에 놓여짐

        ```c
        #include <sys/wait.h>
        pid_t wait(int * statloc);
        // 성공 시 종료된 자식 프로레스의 ID, 실패 시 -1
        // statloc : 반환값이 저장되는 변수의 주소
        ```

        - 좀비 프로세스 소멸 방법2 : waitpid 함수

        ```c
        #include <sys/wait.h>
        pid_t waitpid(pid_t pit, int * statloc, int option);
        // 성공 시 종료된 자식 프로세스의 ID(또는 0), 실패 시 -1
        // pid : 종료를 확인하고자 하는 자식 프로세스의 ID. -1이 전달되면 wait 함수처럼 블로킹 상태에 놓여짐
        // statloc : 반환값이 저장되는 변수의 주소
        // options : 헤더파일 <sys/wait.h>에 선언된 상수 WNOHANG을 인자로 전달하면 블로킹 상태에 있지않고 0을 반환하며 빠져나옴
        ```

    - 시그널 핸들링
        - 시그널 : 특정 상황이 발생했음을 알리기 위해 운영체제가 프로세스에게 전달하는 메시지
        - 시그널 핸들링 : 시그널에 반응해서 시그널과 연관된, 미리 정의된 작업이 진행되는 것
        - 시그널과 signal 함수

            ```c
            #include <signal.h>
            void (*signal(int signo, void(*func)(int)))(int);
            // 시그널 발생시 호출되도록 이전에 등록된 함수의 포인터(주소값) 반환
            // signo : 특정 상황에 대한 정보
            // *func : 특정 상황에서 호출될 함수의 주소 값(포인터)
            ```

            ```c
            #include <unistd.h>
            unsigned int alarm(unsigned int seconds);
            // 0 또는 SIGALRM 시그널이 발생하기 까지 남아있는 시간을 초 단위로 반환
            // 전달된 수에 해당하는 시간(초 단위)이 지나서 SIGARLM 시그널 발생
            ```

        - sigaction 함수
            - signal 함수는 유닉스 계열의 운영체제 별로 동작방식에 있어 약간 차이가 나타남
            - sigaction 함수는 유닉스 계열의 운영체제 별로 차이를 보이지 않음
            ```c
            #include <signal.h>
            int sigaction(int signo, const struct sigaction * act, struct sigaction * oldact);
            // 성공 시 0, 실패 시 -1 반환
            // signo : 시그널의 정보
            // act : 시그널 핸들러의 정보
            // oldact : 이전에 등록된 시그널 핸들러의 함수 포인터(필요없으면 0)

            struct sigaction    // sigaction 함수에서 시그널 핸들러로 사용될 구조체 변수
            {
                void (*sa_handler)(int);
                sigset_t_sa_mask;
                int sa_flags;
            }
            ```
    - 멀티 태스킹 기반의 다중 접속 서버
        - 프로세스 기반의 다중 접속 서버의 구현 모델
            - 1단계 : 에코 서버(부모 프로세스)는 accept 함수호출을 통해서 연결요청을 수락
            - 2단계 : 소켓의 파일 디스크립터를 자식 프로세스를 생성해서 넘겨줌
            - 3단계 : 자식 프로세스는 전달받은 파일 디스크립터를 바탕으로 클라이언트에게 서비스를 제공
    
    - TCP의 입출력 루틴(Routine) 분할
        - 입출력 루틴의 분할
            - 부모 프로세스는 데이터의 수신을 담당, 자식 프로세스는 데이터의 송신을 담당
            - 이점
                - 프로그램의 구현이 한결 수월해짐
                - 데이터 송수신이 잦은 프로그램의 성능향상 -> 데이터의 연속적인 송신

- 프로세스간 통신
    - 프로세스간 통신의 기본 개념
        - 부모 프로세스와 자식 프로세스간 공유해야 될 자원이 있을 경우

        - 파이프 기반의 프로세스간 통신
            - 두 프로세스 간 통신을 위한 파이프 생성
            - 파이프는 프로세스에 속하는 자원이 아닌 운영체제에 속하는 자원 -> fork 함수의 호출에 의한 복사 대상이 아님
            ```c
            #include <unistd.h>
            int pipe(int filedes[2]);
            // 성공시 0, 실패 시 -1 반환
            // filedes[0] : 파이프로 부터 데이터를 수신하는데 사용되는 파일 디스크립터(파이프의 출구)
            // filedes[1] : 데이터를 전송하는데 사용되는 파일 디스크립터(파이프의 입구)
            ```

- 멀티플렉싱(MultiFlexing)
    - IO 멀티플렉싱 기반의 서버
        - 멀티프로세스 서버의 단점
            - 많은 양의 연산이 요구되며, 요구 메모리 공간도 비교적 큰 편
            - 프로세스마다 독립적인 메모리 공간을 유지하기 때문에 상호간에 데이터를 주고받으려면 다소 복잡한 방법을 택하여야 함
        
        - 멀티플렉싱
            - 하나의 통신 채널을 통해서 둘 이상의 데이터(시그널)를 전송하는데 사용되는 기술
            - 물리적 장치의 효율성을 높이기 위해서 최소한의 물리적인 요소만 사용해서 최대한의 데이터를 전달하기 위해 사용되는 기술

            <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet007.png">


    - select 함수의 이해와 서버의 구현
        ```c
        #include <sys/select.h>
        #include <sys/time.h>
        int select(int maxfd, fd_set *readset, fd_set *writeset, fd_set *expectset, const struct timeval * timeout);
        // maxfd : 검사 대상이 되는 파일 디스크립터 수
        // readset : fd_set형 변수에 '수신된 데이터의 존재여부'에 관심 있는 파일 디스크립터 정보를 모두 등록
        // writeset : fd_set형 변수에 '블로킹 없는 데이터 전송의 가능여부'에 관심 있는 파일 디스크립터 정보를 모두 등록
        // exceptset : fd_set형 변수에 '예외사항 발생여부'에 관심 있는 파일 디스크립터 정보
        // timeout : select함수 호출 이후에 무한정 블로킹 상태에 빠지지 않도록 타임아웃(time-out)을 설정하기 위한 인자
        // 반환값 : 오류 발생 시 -1, 타임 아웃 발생시 0, 관심대상으로 등록된 파일 디스크립터에 해당 관심에 관련된 변화 발생 시 0보다 큰 값 반환
        ```
## 5일차(24.06.15)
- 다양한 입출력 함수
    - send & recv 입출력 함수
        - send 함수

            ```c
            #include <sys/socket.h>
            ssize_t send(int sockfd, const void * buf, size_t nbytes, int flags);
            // 성공시 전송된 바이트 수
            // sockfd : 데이터 전송 대상과의 연결을 의미하는 소켓의 파일 디스크립터
            // buf : 전송할 데이터를 저장하고 있는 버퍼의 주소값
            // nbytes : 전송할 바이트 수
            // flagts : 데이터 전송 시 적용할 옵션
            ```
        - recv 함수

            ```c
            # include<sys/socket.h>
            ssize_t send(int sock fd, void * buf, size_t nbytes, int flags);
            // 성공 시 수신한 바이트 수(EOF 전송 시 0), 실패 시 -1
            // sock : 데이터 수신 대상과의 연결을 의미하는 소켓의 파일 디스크립터
            // buf : 수신된 데이터를 저장할 버퍼의 주소값
            // nbyte : 수신할 수 있는 최대 바이트 수
            // flags : 데이터 수신 시 적용할 옵션
            ```
        

        - 리눅스 send&recv의 옵션(s:send, r:recv)
            - send함수과 recv함수의 flags값
            - MSG_OBB : 긴급 데이터(Out-of-band-data)의 전송을 위한 옵션(s,r)
            - MSG_PEEK : 입력 버퍼에 수신된 데이터의 존재 유무 확인(r)
            - MSG_DONTROUTE : 데이터 전송과정에서 라우팅 테이블을 참조하지 않을 것을 요구하는 옵션(s)
            - MSG_DONTWAIT 입출력 함수 호출 과정에서 블로킹 되지 않을 것을 요구하기 위한 옵션(Non-Blocking)(s,r)
            - MSG_WAITALL : 요청한 바이트 수에 해당하는 데이터가 전부 수신될 때까지 호출된 함수가 반환하는 것을 막는 옵션(r)

        - Urgent mode의 동작원리
            - 데이터를 수신하는 대상에게 데이터 처리를 독촉
            - 전송순서가 그대로 유지된다는 TCP의 전송특성은 그대로 유지됨
            - 긴급 메시지는 메시지 처리를 재촉하는데 의미가 있는 것이지 제한된 형태의 메시지를 긴급으로 전송하는데 의미가 있는 것은 아님

        - offset
            - 기본이 되는 위치를 바탕으로 상대적 위치를 표현하는 것
            - 기준점으로부터 어느 쪽으로 얼마나 떨어져 있는지 나타내는 도구
            
            <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet008.png">
        
        - MSG_PEEK & MSG_DONTWAIT
            - MSG_PEEK 옵션을 주고 recv를 호출하면 입력버퍼에 존재하는 데이터가 읽혀지더라도 입력버퍼에서 데이터가 지워지지 않음
            - MSG_DONTWAIT 옵션과 함께 사용하여 블로킹 되지 않는 데이터의 존재 유무를 확인하기 위해 사용

        - readv & writev 함수
            - 데이터를 모아서 전송하고, 모아서 수신하는 기능의
            
            ```c
            #include <sys/uio.h>
            ssize_t writev(int filedes, const struct iovec * iov, int iovcnt);
            // 성공 시 전송된 바이트 수, 실패 시 -1 반환
            // filedes :데이터 전송의 목적지를 나타내는 소켓의 파일 디스크립터(소켓에만 제한되지않고 콘솔 대상의 파일 디스크립터도 전달 가능)
            // iov : 전송할 데이터의 위치와 크기 정보를 담고 있는 구조체 iovec 배열의 주소값
            // iovcnt : 주소 값이 가리키는 배열의 길이 정보

            ssize_t readv(int filedes, const struct iovec * iov, int iovcnt);
            // 성공 시 수신도니 바이트 수, 실패 시 -1 반환
            // filedes :데이를 수신할 파일(혹은 소켓)의 파일 디스크립터
            // iov : 데이터를 저장할 위치와 크기 정보를 담고 있는 구조체 iovec 배열의 주소값
            // iovcnt : 주소 값이 가리키는 배열의 길이 정보

            struct iovec
            {
                void * iov_base; // 버퍼의 주소정보
                size_t iov_len; // 버퍼의 크기정보
            }
            ```
- 소켓과 표준 입출력
    - 표준입출력 함수의 장점
        - 이식성(Portability)가 좋음
        - 버퍼링을 통한 성능의 향상에 도움이 됨
            - 소켓을 생성하면 기본적으로 운영체제에의해 입출력 버퍼가 생성
            - 표준 입출력 함수를 사용하면 추가로 또 하나의 버퍼를 제공받음
            - 소켓의 버퍼는 TCP의 구현을 위한 목적이 강하지만 입출력함수의 버퍼는 성능 향상만을 목적으로 함
            - 버퍼링은 전송하는 데이터의 양과 데이터 이동 횟수 관점에서 성능이 우월함

        - 표준 입출력 함수의 불편사항
            - 양방향 통신이 어려움
            - 읽기에서 쓰기로, 쓰기에서 읽기로 변경할 때 출력 버퍼를 비우는 fflush 함수를 사용해주어야함
            - 파일 디스크립터를 FILE 구조체 포인터로 변경해야함
    
    - 소켓 기반에서의 표준 입출력 함수 사용

- 입출력 스트림의 분리
    - 입력 스트림과 출력 스트림의 분리
        - 스트림 분리의 이점
            - TCP의 입출력 루틴 분할
                - 입력루틴(코드)과 출력루틴의 독립을 통한 구현의 편의성 증대
                - 입력에 상관없이 출력이 가능하게 함으로 인해서 속도의 향상 기대

            - fdopen 함수를 활용한 FILE 포인터 분할
                - FILE 포인터는 읽기모드과 쓰기모드를 구분해야 하므로
                - 읽기 모드와 쓰기 모드의 구분을 통한 구현의 편의성 증대
                - 입력 버퍼와 출력 버퍼를 구분하여 버퍼링 기능의 향상
        
        - 스트림 분리 이후의 EOF에 대한 문제점
            - 파일 포인터를 활용해 분할할 경우, Half-close의 구현이 어려움
            - 출력모드의 파일포인터만 닫더라도 소켓 자체가 완전 종료 됨

        <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet009.png">
    
    - 파일 디스크립터의 복사와 Half-close
        - 파일 디스크립터의 복사
            - 파일 디스크립터를 복사하여 각각의 FILE 포인터를 생성
            - 프로세스의 복사를 동반하지 않는 원본과 복사본이 하나의 프로세스 내에 존재하는 형태
            - dup & dup2
                ```c
                #include <unistd.h>
                int dup(int fildes);
                int dup2(int fildes, int fildes2);  // 복사된 파일 디스크립터의 정수값을 명시적으로 지정할 때 사용
                // 성공 시 복사된 파일 디스크립터, 실패 시 -1
                // fildes : 복사할 파일 디스크립터
                // fildes2 : 명시적으로 지정할 파일 디스크립터의 정수 값
                ```
- epoll
    - epoll의 이해와 활용
        - select 기반의 IO 멀티 플렉싱이 느린 이유
            - select 함수 호출 이후에 항상 등장하는, 모든 파일 디스크립터를 대상으로 하는 반복문
            - select 함수를 호출할 때마다 인자로 매번 전달해야 하는 관찰대상에 대한 정보들 -> 매번 운영체제에게 전달

        - select 함수가 사용되는 경우
            - 서버의 접속자 수가 많지 않음
            - 다양한 운영체제에서 운영 가능해야 함

        - epoll 함수 장점
            - 상태변화의 확인을 위한, 전체 파일 디스크립터를 대상으로 하는 반복문이 필요없음
            - 관찰대상의 정보를 매번 전달할 필요 없음
        
        - epoll 기반 서버 구현에 필요한 함수
            - epoll_create : epoll 파일 디스크립터 저장소 생성
            - epoll_ctl : 저장소에 파일 디스크립터 등록 및 삭제
            - epoll_wait : select 함수와 마찬가지로 파일 디스크립터의 변화를 대기

        - epoll_create
            
            ```c
            #include <sys/epoll.h>
            int epoll_create(int size);
            // 성공 시 epoll 파일 디스크립터, 실패시 -1 반환
            // size : epoll 인스턴스의 크기 정보
            ``` 

        - epoll_ctl

            ```c
            #include <sys/epoll.h>
            int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
            // 성공시 0, 실패시 -1
            // epfd : 관찰대상을 등록할 epoll 인스턴스의 파일 디스크립터
            // op : 관찰 대상의 추가, 삭제 또는 변경 여부 지정
            // fd : 등록할 관찰대상의 파일 디스크립터
            // event : 관찰대상의 관찰 이벤트 유형
            ```

            - op에 전달 가능한 상수
                - EPOLL_CTL_ADD : 파일 디스크립터를 epoll 인스턴스에 등록
                - EPOLL_CTL_DEL : 파일 디스크립터를 epoll 인스턴스에서 삭제
                - EPOLL_CTL_MOD : 등록된 파일 디스크립터의 이벤트 발생상황을 변경

            - event에 저장 가능한 상수
                - EPOLLIN : 수신할 데이터가 존재하는 상황
                - EPOLLOUT : 출력버퍼가 비워져서 당장 데이터를 전송할 수 있는 상황
                - EPOLLPRI : OOB 데이터가 수신된 상황
                - EPOLLET : 이벤트의 감지를 엣지 트리거 방식으로 동작

        - epoll

    - 레벨 트리거(Level Trigger) & 엣지 트리거(Edge Trigger)
        - 레벨 트리거 : 입력 버퍼에 데이터가 남아있는 동안에 계속해서 이벤트가 등록됨
        - 엣지 트리거
            - 데이터가 수신되면 딱 한번 이벤트가 등록됨
            - 데이터의 수신과 데이터가 처리되는 시점을 분리할 수 있음

        - 레벨 트리거와 엣지 트리거의 차이
            - 이벤트가 발생하는 시점
            - 레벨 트리거 : 상태 변수의 현재 상황을 기준
            - 엣지 트리거 : 상태 변수가 변하는 순간(과정)을 기준

        <img src="https://raw.githubusercontent.com/YooWangGwon/Basic-iotNetwork-2024/main/images/iotNet010.png">


- 멀티쓰레드 기반의 서버구현
    - 쓰레드의 이론적 이해
        - 멀티프로세스 기반의 단점
            - 프로세스 생성이라는 부담스러운 작업과정을 거침
            - 두 프로세스 사이에서의 데이터 교환을 위해 별도의 IPC 기법을 적용해야 함

        - 쓰레드 
            - 프로세스 관점에서 별도의 실행흐름을 구성하는 단위
            - 멀티 프로세스의 여러 단점을 최소화하기 위해 설계된 일종의 '경량화 된 프로세스'
            - 하나의 프로세스 안에 쓰레드가 생성되어 해당 프로세스의 힙(heap) 영역은 공유하고 스택영역만 쓰레드 별로 별도로 할당함

        - 쓰레드의 장점
            - 쓰레드의 생성 및 컨텍스트 스위칭은 프로세스의 생성 및 컨텍스트 스위칭보다 빠름
            - 쓰레드 사이에서의 데이터 교환에는 특별한 기법이 필요치 않음

    - 쓰레드의 생성 및 실행
        - 쓰레드의 생성과 실행흐름의 구성
            ```c
            #include <pthread.h>
            int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void*), void *restrict arg)
            // 성공 시 0, 실패 시 0 이외의 값 
            // thread : 생성할 쓰레드의 ID 저장을 위한 변수의 주소값
            // attr : 쓰레드에 부여할 특성 정보의 전달을 위한 매개변수, NULL 전달 시 기본특성
            // start_routine : 쓰레드의 main 함수 역할을 하는, 별도 실행흐름의 시작이 되는 함수의 주소값 저달
            // arg : 전달할 인자의 정보를 담고 있는 변수의 주소 값 전달
            ```

            ```c
            #include <pthread.h>
            int pthread_join(pthread_t thread, void **status);
            // 성공 시 0, 실패 시 0 이외의 값
            // thread : 이 매개변수에 전달되는 ID의 쓰레드가 종료될 때 까지 함수는 반환되지 않음
            // status : 쓰레드의 main 함수가 반환하는 값이 저장될 포인터 변수의 주소 값을 전달
            ```
        - 임계영역 내에서 호출이 가능한 함수
            - 임계영역 : 함수 내에 둘 이상의 쓰레드가 동시에 실행하면 문제를 일으키는 하나 이상의 문장으로 묶여있는 코드불룩
            - 쓰레드에 안전한 함수(Thread-safe function) : 둘 이상의 쓰레드에 의해서 동시에 호출 및 실행되어도 문제를 일으키지 않는 함수
            - 쓰레드에 불안전한 함수(Thread-unsafe function) : 동시 호출 시 문제가 발생할 수 있는 함수

    - 쓰레드의 동기화
        - 동기화가 필요한 경우
            - 동일한 메모리 영역으로의 동시 접근이 발생하는 상황
            - 동일한 메모리 영역에 접근하는 쓰레드의 실행순서를 지정해야 하는 상황

        - 뮤텍스(Mutex)
            - Mutual Exclusion의 줄임말 -> 쓰레드의 동시 접근을 허용하지 않는다는 의미
            - 쓰레드의 동기접근에 대한 해결책
                ```c
                #include <pthread.h>
                pthread_mutex_t mutex;
                int pthread_mutex_init(pthread_mutext_t *mutex, const pthread_mutexattr_t *attr);
                int pthread_mutex_destroy(pthread_mutex_t *mutex);
                int pthread_mutex_lock(pthread_mutext_t *mutex);
                int pthread_mutex_unlock(pthread_mutext_t *mutex);
                // 성공시 0, 실패 시 0 이외의 값 반환
                // mutex : 뮤텍스의 참조 값 저장을 위한 변수의 주소 값
                // attr : 생성하는 뮤텍스의 특성정보를 담고 있는 변수의 주소값 전달, 별도의 특성을 지정하지 않는 경우 NULL 전달
                ```
        
        - 세마포어(Semaphore)
            - 두 개의 원자적 함수로 조작되는 정수 변수로서, 멀티프로그래밍 환경에서 공유 자원에 대한 접근을 제한하는 방법으로 사용됨
            - 0과 1만을 사용 -> '바이너리 세마포어'라고도 부름
            
            ```c
            #include <semaphore>
            int sem_init(sem_t)
            ```