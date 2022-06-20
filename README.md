# 코드 사용법
Linux 시스템에서 CAN통신과 동시에 Serial 통신을 진행한다.


리눅스 환경에서 아래 명령어를 통해 CAN 포트를 Open한다.
```
>> sudo ip link set can0 type can bitrate 250000
>> sudo ip link set can0 up
```
여기서 can0포트는 /dev 경로에서 확인할 수 있다.


CAN Bus 포트의 Up/Down 상태는
```
>> ip a
```
위의 명령어를 통해 확인할 수 있다.


이 상태에서 3개의 파일을 각각 실행하여 CAN과 Serial을 동시에 진행한다.



# CAN통신
CAN통신은 Controller Area Network의 약어로 호스트 컴퓨터 없이 장치들의 통신을 위해 설계된 통신 규격이다.


CAN Bus 프로토콜은 다음과 같은 구조를 갖는다.


![image](https://user-images.githubusercontent.com/17908016/174615744-835ee256-6c80-45ff-9f70-757f157c8f47.png)


메시지의 첫 부분에는 CAN 네트워크에서 각각의 노드를 식별할 수 있도록 각 노드마다 유일한 식별자(11bit or 29bit)를 갖는다.
식별자의 포맷에 따라 통신속도에 차이가 발생한다.
표준 CAN Format은 11bit의 식별자이며 이는 확장 CAN Format(29bit)의 메시지를 수신하더라도 무시하게 된다.


그러나 확장형 포맷은 양쪽의 메시지 포맷에 대해 모두 송/수신이 가능하다.


네트워크의 모든 노드는 메시지를 수신하고 식별자를 확인 후 필요한 ID일 경우 메시지를 수신하고 그렇지 않을 경우 메시지를 무시한다.



* CAN통신 개념
https://www.fescaro.com/ko/archives/249

* Serial 통신 코드 출처
https://onece.tistory.com/91

* CAN통신 코드 출처
https://github.com/craigpeacock/CAN-Examples
