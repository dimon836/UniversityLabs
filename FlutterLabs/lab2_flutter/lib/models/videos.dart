import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import '../utils/fetchVideos.dart';

class Videos extends ChangeNotifier {
  late List<Map<String, dynamic>> _videos = [];

  void update() {
    _videos.clear();
    getVideos().then((videos) {
      _videos = videos.map((element) {
        element['isLiked'] = 'null';
        return element;
      }).toList();
      notifyListeners();
    });
  }

  List getAll() {
    return _videos;
  }

  Map getVideoById(dynamic id) {
    return _videos.firstWhere((element) => element['id'] == id);
  }

  void like(dynamic id) {
    final video = getVideoById(id);
    if(video['isLiked'] == 'liked') {
      // already liked
      video['isLiked'] = 'null';
      video['likes']--;
    } else {
      if(video['isLiked'] == 'disliked') {
        video['dislikes']--;
      }
      video['isLiked'] = 'liked';
      video['likes']++;
    }

    video['views']++;

    notifyListeners();
  }

  void dislike(dynamic id) {
    final video = getVideoById(id);
    if(video['isLiked'] == 'disliked') {
      // already liked
      video['isLiked'] = 'null';
      video['dislikes']--;
    } else {
      if(video['isLiked'] == 'liked') {
        video['likes']--;
      }
      video['isLiked'] = 'disliked';
      video['dislikes']++;
    }

    video['views']++;

    notifyListeners();
  }
}
