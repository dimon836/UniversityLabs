import 'dart:convert';
import 'package:http/http.dart' as http;

Future<List<Map<String, dynamic>>> getVideos() async {
  final response = await http.get(Uri.parse(
      "https://raw.githubusercontent.com/dimon836/UniversityLabs/branch_for_lab4_flutter/FlutterLabs/lab2_flutter/data/videos.json"));
  print('response ${response.body}');

  if (response.statusCode == 200) {
    final list = (jsonDecode(response.body) as List);
    return list.map((e) => e as Map<String, dynamic>).toList();
  } else {
    throw Exception('Неудача при загрузке');
  }
}
