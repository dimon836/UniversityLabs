import 'package:flutter/material.dart';
import '../components/video_preview.dart';
import '../videos.dart';

class MainPage extends StatelessWidget {
  static final double _videoMargin = 15.0;

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      child: Column(
        children: getVideos()
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
                ),
              ),
            )
            .toList(),
      ),
    );
  }
}
