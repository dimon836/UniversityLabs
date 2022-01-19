import 'dart:math';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class AnimatedBarChartPart extends AnimatedWidget {
  late final _sizeTween;
  static final _opacityTween = Tween<double>(begin: 0.1, end: 1);

  final Color color;
  final String label;
  final double percentage;

  AnimatedBarChartPart(
      {Key? key,
      required Animation<double> animation,
      required this.label,
      required this.percentage,
      required this.color})
      : super(key: key, listenable: animation) {
    this._sizeTween = Tween<double>(begin: 1, end: this.percentage);
  }

  @override
  Widget build(BuildContext context) {
    final animation = listenable as Animation<double>;
    return Column(
      mainAxisAlignment: MainAxisAlignment.end,
      children: [
        Opacity(
          opacity: _opacityTween.evaluate(animation),
          child: Container(
            margin: const EdgeInsets.symmetric(vertical: 10),
            color: color,
            height: _sizeTween.evaluate(animation),
            width: 20,
          ),
        ),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(label),
          ],
        ),
      ],
    );
  }
}

class AnimatedBarChart extends AnimatedWidget {
  final Map<String, double> data;

  const AnimatedBarChart(
      {Key? key, required Animation<double> animation, required this.data})
      : super(key: key, listenable: animation);
  static final _colorTween = ColorTween(
    begin: Colors.black,
    end: Colors.primaries[Random().nextInt(Colors.primaries.length)],
  );

  @override
  Widget build(BuildContext context) {
    final animation = listenable as Animation<double>;
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 20),
      child: SizedBox(
        height: 400,
        child: Card(
          child: Padding(
            padding: EdgeInsets.fromLTRB(0, 15, 0, 15),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: data.keys.map(
                (key) => AnimatedBarChartPart(
                  animation: animation,
                  label: key,
                  percentage: data[key]!,
                  color: _colorTween.evaluate(animation)!,
                ),
              ).toList(),
            ),
          ),
        ),
      ),
    );
  }
}

class HotaResourcesPage extends StatefulWidget {
  HotaResourcesPage();

  @override
  State<StatefulWidget> createState() => _HotaResourcesPageState();
}

class _HotaResourcesPageState extends State<HotaResourcesPage>
    with SingleTickerProviderStateMixin {
  late Animation<double> animation;
  late AnimationController controller;

  @override
  void initState() {
    super.initState();
    controller =
        AnimationController(duration: const Duration(seconds: 3), vsync: this);
    animation =
        CurvedAnimation(parent: controller, curve: Curves.easeInOutCubic);
          // ..addStatusListener((status) {
          //   if (status == AnimationStatus.completed) {
          //     controller.reverse();
          //   } else if (status == AnimationStatus.dismissed) {
          //     controller.forward();
          //   }
          // });
    controller.forward();
  }

  @override
  void dispose() {
    controller.stop();
    controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return CustomScrollView(slivers: [
      SliverFillRemaining(
        hasScrollBody: false,
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            AnimatedBarChart(animation: animation, data: {
              "Древесина": 50,
              "Ртуть": 20,
              "Руда": 50,
              "Сера": 20,
              "Самоцветы": 20,
              "Кристалы": 20,
              "Золото": 0,
            })
          ],
        ),
      ),
    ]);
  }
}
