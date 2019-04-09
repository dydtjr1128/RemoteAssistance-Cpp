# RemoteAssistance-Cpp
RemoteAssistance like TeamViewer C++ version

https://dydtjr1128.github.io/RemoteAssistance-Cpp/

## ToDo

<p>
  <ul> 
    <li>- [x] Screen capture</li>    
    <li>- [x] Double buffering</li>
    <li>- [ ] Add image compress(JPEG)</li>    
    <li>- [ ] Add network code(socket)</li>
    <li>- [ ] 변경데이터 전송 알고리즘 구상</li>
    <li>- [ ] Boost asio 또는 iocp </li>
    <li>- [ ] SIMD compare </li>
    <li>- [ ] ★현재 CPU로 연산하여 이미지를 얻지만 OpenGL기반으로 gpu를 이용하여 구현해 보기 </li>
  </ul>
</p>

## Sample
![gif6](https://user-images.githubusercontent.com/19161231/50547144-9a3f6c00-0c77-11e9-90c4-f5cca7644c9b.gif)


## Structure
<pre>
Client <-> Broker server(Session) <-> Client
  ↑                                     ↑
  └─────────────────────────────────────┘
                Data send
</pre>

![image](https://user-images.githubusercontent.com/19161231/54978008-58a62f00-4fe2-11e9-9d9a-df5b42e840ca.png)
![image](https://user-images.githubusercontent.com/19161231/54977978-3d3b2400-4fe2-11e9-808a-08f9a3d4cad9.png)

## 이미지 전송 알고리즘 구상 방안

<p>
  <img src="https://user-images.githubusercontent.com/19161231/48710631-5440c280-ec4c-11e8-9808-39203fa8d10b.png" width="50%">
</p>
이 경우 비교 방법 등도 고려 해야함 (SIMD 등 사용?)




</br> 
<a href="mailto:dydtjr1994@gmail.com" target="_blank">
  <img src="https://img.shields.io/badge/E--mail-Yongseok%20choi-yellow.svg">
</a>
<a href="https://blog.naver.com/cys_star" target="_blank">
  <img src="https://img.shields.io/badge/Blog-cys__star%27s%20Blog-blue.svg">
</a>

