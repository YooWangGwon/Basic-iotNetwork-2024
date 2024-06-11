# Basic-iotNetwork-2024
부경대학교 2024 IoT 개발자 과정 iot 네트워크 프로그래밍 리포지토리

## 1일차(24.06.11)
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
        - 2 : 표준예러(Standard Error)

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
            char            sin_zero[8];    //  사용되지 않음
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
            - 구조체 변수 in_addr를 이용하는 형태 -> 변환된 IP 주소를 구조체 sockaddr_in에 선언되어있는 addr_in 구조체 변수에 대입하는 과정이 필요X
            ```c
            #include <arpa/inet.h>
            int inet_aton(const char * string, struct in_addr * addr);
            // string : 변환할 IP 주소 정보를 담고있는 문자열의 주소값, addr : 변환된 정보를 저장할 in_addr 구조체 변수의 주소 값 전달
            // 성공 시 1(true), 실패 시 0(false) 반환
            ```