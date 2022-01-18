// in future would be replaced by requests
List videos = [
  {
    'id': '1',
    'previewImage': 'resources/images/videos/1.jpg',
    'description': 'Верстка мобільного застосунку. Flutter. Лекція 3',
    'length': '1:09:16',
    'channelAvatarImage': 'resources/images/channels/serhiy_tytenko.jpg',
    'channelName': 'Сергій Титенко | Web & Mobile Development',
    'views': '562 просмотра',
    'shortUploadedAt': '2 года назад',
    'uploadedAt': '21 сент. 2019 г.',
    'likes': '8',
    'dislikes': '0',
    'subscribers': '337',
    'specification': '''
    Завдання на практичну роботу:
    1) Побудувати ієрархію віджетів. А саме: Container, Column, Row, Expanded
    2) Продемонструвати стилізацію віджетів. А саме: колір, розмір, тінь, бекграунд
    3) Побудувати коректне розміщення віджетів за допомогою crossAxisAlignment, mainAxisAlignment
    4) На основі зазначенних вище завдань створити імітацію верстки популярного мобільного додатку (наприклад: фейсбук, інстаграм, твіттер і т.д.)
                        
    Сергій Титенко.
    Flutter: мобільна розробка.
    КПІ ім. Ігоря Сікорського.
    Кафедра АПЕПС. ТЕФ.'''
  },
  {
    'id': '2',
    'previewImage': 'resources/images/videos/2.jpg',
    'description': 'Material design. Scaffold widget. Flutter. Лекція 4',
    'length': '46:54  ',
    'channelAvatarImage': 'resources/images/channels/serhiy_tytenko.jpg',
    'channelName': 'Сергій Титенко | Web & Mobile Development',
    'views': '406 просмотра',
    'shortUploadedAt': '2 года назад',
    'uploadedAt': '25 нояб. 2019 г.',
    'likes': '9',
    'dislikes': '0',
    'subscribers': '337',
    'specification': '''
    Завдання на практичну роботу:
    1) Побудувати Scaffold віджет, Drawer, FloatingButton, BottomNavigationBar
    2) Анімований BottomNavigationBar
    3) Анімований Hero віджет
                        
    Сергій Титенко.
    Flutter: мобільна розробка.
    КПІ ім. Ігоря Сікорського.
    Кафедра АПЕПС. ТЕФ.'''
  },
  {
    'id': '3',
    'previewImage': 'resources/images/videos/3.jpg',
    'description': 'Основи дизайну: кольори, шрифти, іконки.Частина 2',
    'length': '25:44',
    'channelAvatarImage': 'resources/images/channels/serhiy_tytenko.jpg',
    'channelName': 'Сергій Титенко | Web & Mobile Development',
    'views': '173 просмотра',
    'shortUploadedAt': '1 год назад',
    'uploadedAt': '20 февр. 2020 г.',
    'likes': '7',
    'dislikes': '0',
    'subscribers': '337',
    'specification': '''
    Основи веб-розробки.

    Завдання:
    Створити макет сайту-візитки про себе. З інформацією про те хто ви, звідки, де навчалися, навички та цілі.
    Рекомендовані ресурси:
    Google Fonts - для обрання та завантаження шрифтів.
    Flaticon, Font Awesome - для векторних іконок.
    Coolors - для підбору кольорів.
                        
    Сергій Титенко.
    Flutter: мобільна розробка.
    КПІ ім. Ігоря Сікорського.
    Кафедра АПЕПС. ТЕФ.'''
  }
];

Map getVideoById(dynamic id) {
  return videos.firstWhere((element) => element['id'] == id);
}

List getVideos() {
  return videos;
}
