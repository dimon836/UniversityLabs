import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_svg/flutter_svg.dart';
import 'package:rainbow_container/rainbow_container.dart';
import './pages/main_page.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'MyTube - YouTube Clone',
      theme: ThemeData(
        brightness: Brightness.dark,
        // primarySwatch: Colors.grey,

        elevatedButtonTheme: ElevatedButtonThemeData(
          style: ElevatedButton.styleFrom(
            onPrimary: Colors.white,
            primary: Colors.white12,
          ).copyWith(
            shape: MaterialStateProperty.all<RoundedRectangleBorder>(
              RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(18.0),
                side: BorderSide(color: Colors.transparent),
              ),
            ),
          ),
        ),
        outlinedButtonTheme: OutlinedButtonThemeData(
          style: ElevatedButton.styleFrom(
            onPrimary: Colors.white,
            primary: Colors.white10,
          ),
        ),
        textButtonTheme: TextButtonThemeData(
          style: TextButton.styleFrom(
            primary: Colors.white,
          ),
        ),
      ),
      themeMode: ThemeMode.dark,
      home: App(),
    );
  }
}

class App extends StatefulWidget {
  const App({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _AppState();
}

class _AppState extends State<App> {
  int _selectedIndex = 0;
  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();

  void _openEndDrawer() {
    _scaffoldKey.currentState!.openEndDrawer();
  }

  void _closeEndDrawer() {
    Navigator.of(context).pop();
  }

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }

  static final _indexToPageMap = [
    MainPage(),
    Text('Не разработано'),
    Text('Не разработано'),
    Text('Не разработано'),
    Text('Не разработано'),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: _scaffoldKey,
      appBar: AppBar(
        leading: SvgPicture.asset(
          'resources/images/YouTube-Icon-Full-Color-Logo.wine.svg',
          semanticsLabel: 'YouTube Logo',
          fit: BoxFit.contain,
        ),
        title: Text(
          'MyTube',
          style: TextStyle(
              fontFamily: 'YouTubeSans',
              fontWeight: FontWeight.w700,
              fontSize: 32,
              letterSpacing: -2),
        ),
        titleSpacing: -3,
        actions: <Widget>[
          IconButton(
              icon: const Icon(Icons.notifications_outlined),
              tooltip: 'Показать уведомления',
              onPressed: () {
                Navigator.push(context, MaterialPageRoute<void>(
                  builder: (BuildContext context) {
                    return Scaffold(
                      appBar: AppBar(
                        title: const Text('Уведомления'),
                      ),
                      body: const Center(
                        child: Text(
                          'Нет новых уведомлений',
                          style: TextStyle(fontSize: 24),
                        ),
                      ),
                    );
                  },
                ));
              }),
          IconButton(
            icon: const Icon(Icons.search),
            tooltip: 'Поиск',
            onPressed: () {
              ScaffoldMessenger.of(context)
                  .showSnackBar(const SnackBar(content: Text('В разработке')));
            },
          ),
          IconButton(
            onPressed: _openEndDrawer,
            icon: CircleAvatar(
              radius: 20,
              backgroundImage:
                  AssetImage('resources/images/default-avatar.png'),
            ),
          )
        ],
        bottom: PreferredSize(
          preferredSize: Size.fromHeight(45),
          child: Container(
            height: 45,
            padding: EdgeInsets.fromLTRB(10, 0, 0, 10),
            child: ListView(
              scrollDirection: Axis.horizontal,
              shrinkWrap: true,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    OutlinedButton(
                      child: Row(
                        children: [
                          const Icon(Icons.explore_outlined),
                          const Text('Навигатор'),
                        ],
                      ),
                      onPressed: () {},
                      // style: ButtonStyle(
                      //   backgroundColor:
                      //       MaterialStateProperty.all<Color>(Colors.black12),
                      // ),
                    ),
                    VerticalDivider(
                      thickness: 1,
                    ),
                    Container(
                      child: ElevatedButton(
                          child: const Text('Все'),
                          onPressed: () {},
                          style: ElevatedButton.styleFrom(
                            onPrimary: Colors.black,
                            primary: Colors.white,
                          )),
                    ),
                    Container(
                      margin: const EdgeInsets.only(left: 5),
                      child: ElevatedButton(
                        child: const Text('Просмотрено'),
                        onPressed: () {},
                      ),
                    ),
                    RainbowContainer(
                      decoration: BoxDecoration(
                          borderRadius: BorderRadius.circular(16)),
                      // margin: const EdgeInsets.only(left: 5),
                      child: ElevatedButton(
                        child: const Text('Heroes 3: HotA'),
                        onPressed: () {},
                      ),
                    ),
                    Container(
                      margin: const EdgeInsets.only(left: 5),
                      child: ElevatedButton(
                        child: const Text('Игры'),
                        onPressed: () {},
                      ),
                    ),
                    Container(
                      margin: const EdgeInsets.only(left: 5),
                      child: ElevatedButton(
                        child: const Text('Рок'),
                        onPressed: () {},
                      ),
                    ),
                    Container(
                      margin: const EdgeInsets.only(left: 5),
                      child: ElevatedButton(
                        child: const Text('Математика'),
                        onPressed: () {},
                      ),
                    ),
                    Container(
                      margin: const EdgeInsets.only(left: 5),
                      child: ElevatedButton(
                        child: const Text('Музыка'),
                        onPressed: () {},
                      ),
                    ),
                  ],
                ),
              ],
            ),
          ),
        ),
      ),
      bottomNavigationBar: BottomNavigationBar(
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.home_outlined),
            activeIcon: Icon(Icons.home),
            label: 'Главная',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.movie_creation_outlined),
            activeIcon: Icon(Icons.movie_creation),
            label: 'Shorts',
          ),
          BottomNavigationBarItem(
            icon: Icon(
              Icons.add_circle_outline,
              size: 20,
            ),
            activeIcon: Icon(
              Icons.add_circle,
              size: 26,
            ),
            label: '',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.subscriptions_outlined),
            activeIcon: Icon(Icons.subscriptions),
            label: 'Подписки',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.video_library_outlined),
            activeIcon: Icon(Icons.video_library),
            label: 'Библиотека',
          ),
        ],
        currentIndex: _selectedIndex,
        selectedItemColor: Colors.white,
        onTap: _onItemTapped,
        showUnselectedLabels: true,
      ),
      endDrawer: Drawer(
        child: ListView(
          padding: EdgeInsets.zero,
          children: [
            const DrawerHeader(
              child: Text('Мой аккаунт'),
            ),
            ListTile(
              title: const Text('Мой канал'),
              onTap: () {
                ScaffoldMessenger.of(context).showSnackBar(
                    const SnackBar(content: Text('В разработке')));
                Navigator.pop(context);
              },
            ),
            ListTile(
              title: const Text('Что-то другое...'),
              onTap: () {
                ScaffoldMessenger.of(context).showSnackBar(
                    const SnackBar(content: Text('В разработке')));
                Navigator.pop(context);
              },
            ),
          ],
        ),
      ),
      endDrawerEnableOpenDragGesture: false,

      body: _indexToPageMap.elementAt(_selectedIndex),
    );
  }
}
