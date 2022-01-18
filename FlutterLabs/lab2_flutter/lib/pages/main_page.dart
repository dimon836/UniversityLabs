import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/videos.dart';
import '../components/video_preview.dart';

class MainPage extends StatelessWidget {
  static final double _videoMargin = 15.0;
  final VoidCallback incrementSubscribeCounter;

  MainPage({required this.incrementSubscribeCounter});

  @override
  Widget build(BuildContext context) {
    return Consumer<Videos>(
        builder: (context, videos, child) {
          return SingleChildScrollView(
            child: Column(
              children: videos.getAll()
                  .map(
                    (e) => Container(
                      padding: EdgeInsets.fromLTRB(0, 0, 0, _videoMargin),
                      child: VideoPreview(
                        id: e['id'],
                        previewImage: e['previewImage'],
                        description: e['description'],
                        length: e['length'],
                        channelAvatarImage: e['channelAvatarImage'],
                        channelName: e['channelName'],
                        views: e['views'],
                        shortUploadedAt: e['shortUploadedAt'],
                        incrementSubscribeCounter: this.incrementSubscribeCounter,
                      ),
                    ),
              )
                  .toList(),
            ),
          );
        }
    );
  }
}
