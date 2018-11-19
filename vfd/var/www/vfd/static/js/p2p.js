var P2PObj = function () {
    var peer, conn;
    var self_id;
    var peer_id;

    var onError = function(err) {
        PageUtil.error(err.type);
        if (err.type == 'network') {
        }
    }

    var onOpen = function() {
        peer.on('connection', onConnection);

        navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
        if (navigator.getUserMedia) {
            navigator.getUserMedia({audio: true, video: true}, scb_getUserMedia, ecb_getUserMedia);
        } else {
            PageUtil.error('浏览器不支持音视频！');
        }
    }

    var scb_getUserMedia = function(stream) {
        //本地音视频OK
        window.localStream = stream;
        var video = $('#self-camera video')[0];
        video.src = window.URL.createObjectURL(stream);
        peer.on('call', onCall);
    }

    var ecb_getUserMedia = function(error) {
        PageUtil.error("没有找到音视频设备！");
    }

    var onConnection = function(connection) {
        conn = connection;
        peer_id = connection.peer;
        $("#p2p-send").removeClass("hidden");
        conn.on('data', handleMessage);
    }

    var handleMessage = function(data) {
       //收到对方消息，更新消息文本框
        $("#p2p-messages").append(data.from + ': ' + data.message+'\n');
        if (data.from == self_id) {
            $("#p2p-message").val('');
        }
    }

    function onCall(call) {
        call.answer(window.localStream);
        call.on('stream', onStream);
    }

    function onStream(stream) {
        window.peer_stream = stream;
        var video = $('#peer-camera video')[0];
        video.src = window.URL.createObjectURL(stream);
    }

    function go() {
        self_id = uuid.replace(/:/g, '-');

        peer = new Peer(self_id, {
            host: '192.168.0.80',
            port: 9000,
            path: '/peerjs/',
            debug: 3,
            //config: {'iceServers': [
            //    { url: 'stun:stun1.l.google.com:19302' },
            //    { url: 'turn:numb.viagenie.ca', credential: 'muazkh', username: 'webrtc@live.com' }
            //]}
        });

        peer.on('error', onError);
        peer.on('open', onOpen);
    }

    var handleActions = function(){
        $('body')
        .on('click', '#p2p-send', function(e) {
            e.preventDefault();
            var message = $("#p2p-message").val();
            var data = {'from': self_id, 'message': message};
            conn.send(data);
            handleMessage(data);
        })
    }

    return {
        init: function () {
            go();
            handleActions();
        }
    };
}();

