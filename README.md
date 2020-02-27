# RemoteAssistance-Cpp
RemoteAssistance like TeamViewer C++ version

https://dydtjr1128.github.io/RemoteAssistance-Cpp/

It also made java swing version => [Link](https://github.com/dydtjr1128/RemoteAssistance-JAVA)


## ToDo

<p>
  <ul> 
    <li>- [x] Screen capture</li>    
    <li>- [x] Double buffering</li>
    <li>- [ ] Add network code(socket)</li>
    <li>- [ ] Plan the Image Transmission</li>
    <li>- [ ] Boost asio 또는 IOCP </li>
    <li>- [ ] SIMD compare </li>
    <li>- [ ] Capture screen based OpenGL </li>
  </ul>
</p>

## Sample demo
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

## A Plan about the Image Transmission Algorithm

<p>
  <img src="https://user-images.githubusercontent.com/19161231/48710631-5440c280-ec4c-11e8-9808-39203fa8d10b.png" width="50%">
</p>

1. Unconditionally Full Data Transfer
2. Compare with previous data and transfer if different
3. Import data from random locations, compare with previous data, and transfer if different
4. Divide image data into grid and compare each grid in parallel

This case must be considered comparison process(like SIMD..)

</br> 
<a href="mailto:dydtjr1994@gmail.com" target="_blank">
  <img src="https://img.shields.io/badge/E--mail-YongSeok%20Choi-yellow.svg">
</a>
<a target="_blank" href="https://dydtjr1128.github.io/" target="_blank">
  <img src="https://img.shields.io/badge/Blog-dydtjr1128's%20blog-blue.svg">
</a> 
