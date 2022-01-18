import 'package:flutter/material.dart';

class SubscriptionsPage extends StatelessWidget {
  final int totalSubscribeClicks;
  final VoidCallback onClick;

  const SubscriptionsPage(
      {Key? key, required this.totalSubscribeClicks, required this.onClick})
      : super(key: key);

  @override
  Widget build(BuildContext context) {
    return CustomScrollView(slivers: [
      SliverFillRemaining(
        hasScrollBody: false,
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Text("${this.totalSubscribeClicks}"),
            TextButton(
              onPressed: () {
                onClick();
              },
              child: Text("SUBSCRIBE"),
            ),
          ],
        ),
      ),
    ]);
  }
}
