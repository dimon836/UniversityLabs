import 'package:flutter/material.dart';
import 'package:url_launcher/url_launcher.dart';
import '../videos.dart';

class VideoPage extends StatelessWidget {
  static const TextStyle BottomInfoStyle = TextStyle(
    fontWeight: FontWeight.w600,
    color: Color(0xFFAAAAAA),
    fontSize: 12,
    fontFamily: 'Roboto',
  );

  final String id;

  late final String _previewImage;
  late final String _description;
  late final String _length;

  late final String _channelAvatarImage;
  late final String _channelName;
  late final String _views;
  late final String _uploadedAt;

  late final String _likes;
  late final String _dislikes;
  late final String _subscribers;

  late final String _specification;

  VideoPage({required this.id}) {
    Map video = getVideoById(this.id);
    this._previewImage = video['previewImage'];
    this._description = video['description'];
    this._length = video['length'];
    this._channelAvatarImage = video['channelAvatarImage'];
    this._channelName = video['channelName'];
    this._views = video['views'];
    this._uploadedAt = video['uploadedAt'];
    this._likes = video['likes'];
    this._dislikes = video['dislikes'];
    this._subscribers = video['subscribers'];
    this._specification = video['specification'];
  }

  @override
  Widget build(BuildContext context) {
    return Hero(
      tag: this.id,
      child: Material(
        child: SingleChildScrollView(
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            mainAxisSize: MainAxisSize.min,
            children: [
              Container(
                width: double.infinity,
                height: 200,
                margin: EdgeInsets.fromLTRB(0, 0, 0, 10),
                decoration: BoxDecoration(
                  image: DecorationImage(
                    image: AssetImage(this._previewImage),
                    fit: BoxFit.cover,
                  ),
                ),
                child: Stack(
                  children: [
                    Positioned(
                      top: 5,
                      left: 10,
                      child: IconButton(
                        onPressed: () {
                          Navigator.of(context).pop();
                        },
                        icon: Icon(Icons.keyboard_arrow_down),
                      ),
                    )
                  ],
                ),
              ),
              Container(
                padding: EdgeInsets.fromLTRB(10, 0, 10, 0),
                child: Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Flexible(
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Row(
                            mainAxisSize: MainAxisSize.min,
                            children: [
                              Flexible(
                                child: Container(
                                  margin: EdgeInsets.only(bottom: 10),
                                  child: Text(
                                    this._description,
                                    style: TextStyle(fontSize: 18),
                                    maxLines: 2,
                                    softWrap: true,
                                    overflow: TextOverflow.ellipsis,
                                  ),
                                ),
                              ),
                            ],
                          ),
                          Row(
                            children: [
                              Container(
                                child: Text(
                                  this._views,
                                  style: BottomInfoStyle,
                                ),
                              ),
                              Container(
                                margin: EdgeInsets.fromLTRB(5, 0, 5, 0),
                                width: 5,
                                height: 5,
                                decoration: BoxDecoration(
                                  color: Color(0xFFAAAAAA),
                                  shape: BoxShape.circle,
                                ),
                              ),
                              Container(
                                child: Text(
                                  this._uploadedAt,
                                  style: BottomInfoStyle,
                                ),
                              ),
                            ],
                          ),
                        ],
                      ),
                    ),
                  ],
                ),
              ),
              Container(
                height: 20,
              ),
              Container(
                padding: EdgeInsets.fromLTRB(15, 0, 15, 0),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    TextButton(
                      onPressed: () {},
                      child: Column(
                        children: [
                          Icon(Icons.thumb_up_outlined),
                          Divider(
                            thickness: 0,
                            height: 3,
                          ),
                          Text(this._likes),
                        ],
                      ),
                    ),
                    TextButton(
                      onPressed: () {},
                      child: Column(
                        children: [
                          Icon(Icons.thumb_down_outlined),
                          Divider(
                            thickness: 0,
                            height: 3,
                          ),
                          Text(this._dislikes),
                        ],
                      ),
                    ),
                    TextButton(
                      onPressed: () {},
                      child: Column(
                        children: [
                          Icon(Icons.send_outlined),
                          Divider(
                            thickness: 0,
                            height: 3,
                          ),
                          Text('Share'),
                        ],
                      ),
                    ),
                    TextButton(
                      onPressed: () {},
                      child: Column(
                        children: [
                          Icon(Icons.playlist_add),
                          Divider(
                            thickness: 0,
                            height: 3,
                          ),
                          Text('Save'),
                        ],
                      ),
                    ),
                  ],
                ),
              ),
              Divider(
                thickness: 1,
              ),
              Container(
                padding: EdgeInsets.fromLTRB(5, 0, 15, 0),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    // channel info
                    MaterialButton(
                      onPressed: () {  },
                      child: Container(
                        margin: EdgeInsets.fromLTRB(0, 0, 10, 0),
                        child: Row(
                          mainAxisAlignment: MainAxisAlignment.start,
                          mainAxisSize: MainAxisSize.min,
                          children: [
                            Container(
                              height: 36,
                              width: 36,
                              margin: EdgeInsets.fromLTRB(0, 0, 10, 0),
                              child: CircleAvatar(
                                backgroundImage:
                                    AssetImage(this._channelAvatarImage),
                              ),
                            ),
                            Container(
                              width: 80,
                              child: Column(
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: [
                                  Row(
                                    mainAxisSize: MainAxisSize.min,
                                    children: [
                                      Flexible(
                                        child: Container(
                                          child: Text(
                                            this._channelName,
                                            style: TextStyle(fontSize: 14),
                                            maxLines: 1,
                                            softWrap: false,
                                            overflow: TextOverflow.ellipsis,
                                          ),
                                        ),
                                      ),
                                    ],
                                  ),
                                  Row(
                                    mainAxisSize: MainAxisSize.min,
                                    children: [
                                      Flexible(
                                        child: Container(
                                          child: Text(
                                            '${this._subscribers} подписчиков',
                                            style: TextStyle(
                                              fontSize: 12,
                                              color: Colors.grey,
                                            ),
                                            maxLines: 1,
                                            softWrap: true,
                                            overflow: TextOverflow.ellipsis,
                                          ),
                                        ),
                                      ),
                                    ],
                                  ),
                                ],
                              ),
                            ),
                          ],
                        ),
                      ),
                    ),

                    TextButton(
                      onPressed: () {  },
                      child: Container(
                        padding: EdgeInsets.all(8.0),
                        child: Text(
                          'ПОДПИСАТЬСЯ',
                          style: TextStyle(
                            color: Colors.red,
                            fontSize: 16,
                          ),
                        ),
                      ),
                    ),

                    Container(
                      child: IconButton(
                        icon: Icon(Icons.notifications_outlined),
                        onPressed: () {},
                      ),
                    )
                  ],
                ),
              ),
              Divider(
                height: 1,
              ),
              Container(
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.start,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      '${this._specification}',
                      style: TextStyle(
                        fontSize: 12,
                        color: Colors.white,
                      ),
                    ),
                    InkWell(
                      child: new Text(
                        '    http://apeps.kpi.ua/',
                        style: TextStyle(
                          fontSize: 12,
                          color: Colors.blue,
                        ),
                      ),
                      onTap: () => launch('http://apeps.kpi.ua/')
                    ),
                  ],
                  ),
                ),
            ],
          ),
        ),
      ),
    );
  }
}
